/*
    @author: Nenya Edjah

    This is a lightweight bignum library for C/C++. It allows for arbitrarily
    large signed integers, albeit the maximum size must be prefedined at
    compilation time. Therefore, this library simply extends the maximum
    representable integer to a value that will hopefully be suitable for your
    use case.

    To customize integer sizing, you must #define an appropriate value for
    DESIRED_PRECISION prior to #include-ing this library in your source files.
    For example, if the largest number you antipicate is 10^450, you would
    put this at the top of your file source file:

        #define DESIRED_PRECISION 450

    If you define the value to be too low, then you will encounter undefined
    behavior when performing operations with large numbers. If you set the
    value to be too high, then memory usage will be inefficient. The default
    value of DESIRED_PRECISION is 256 which effectively extends the range of
    representable integers to at least [-10^256, 10^256].

    String conversion only support base 10

    This library also comes with built-in functions for
        * Addition and subtraction
        * Multiplication
        * Division
        * (Modular) Exponentiation
        * Comparison testing
        * String conversion and parsing

    Maybe in the future:
        - Karatsuba multiplication
        - Dynamically allocated bignums


    TODO:
        * Clean up style
        * Better documentation for each function
        * Optimize arithmetic operations / library as a whole
        * Switch to using bit masks/shifts for modulo and floor division :(

*/

#include <ctype.h>

#ifndef __UTILITYH__
#include "utility.h"
#endif


#define BASE_SHIFT 30L
#define BASE (1L << BASE_SHIFT)
#define BASE_MASK (BASE - 1L)
#define CHARS_PER_DIGIT 9

#define KARATSUBA_CUTOFF 320

#ifdef DESIRED_PRECISION
#define MAX_DIGITS (DESIRED_PRECISION + 8) / 9
#endif

#ifndef MAX_DIGITS
#define MAX_DIGITS 64
#endif

typedef struct bignum {
    int digits[MAX_DIGITS];
    int size;
    int sign;
} bignum;


bignum __BIGNUM_ZERO  = {.digits = {0}, .size = 1, .sign = 1};
bignum __BIGNUM_ONE   = {.digits = {1}, .size = 1, .sign = 1};
bignum __BIGNUM_TWO   = {.digits = {2}, .size = 1, .sign = 1};

bignum* BIGNUM_ZERO = &__BIGNUM_ZERO;
bignum* BIGNUM_ONE  = &__BIGNUM_ONE;
bignum* BIGNUM_TWO  = &__BIGNUM_TWO;

// TOOD: implement more sophisticated (efficient) memory allocation
bignum* alloc_empty_bignum() {
    return calloc(1, sizeof(bignum));
}

void bignum_free(bignum* b) {
    free(b);
}

bignum* __bignum_cleanup(bignum* b) {
    if (b->size == 0) {
        b->digits[0] = 0;
        b->size = 1;
    }
    while (b->size > 1 && b->digits[b->size - 1] == 0) {
        b->size -= 1;
    }
    if (b->size == 1 && b->digits[0] == 0) {
        b->sign = 1;
    }
    return b;
}

static inline bignum* make_bignum_zero(bignum* b) {
    b->size = b->sign = 1;
    b->digits[0] = 0;
    return b;
}

static inline bignum* bignum_copy(bignum* b) {
    bignum* x = alloc_empty_bignum();
    *x = *b;
    return x;
}

/* Parsing and conversion to/from other data types */
bignum* bignum_from_string(char* s) {
    bignum* b = alloc_empty_bignum();
    b->sign = 1;

    // skipping past leading whitespace
    int i = 0;
    while (isspace(s[i])) {
        i += 1;
    }

    // detecting sign
    if (s[i] == '-' || s[i] == '+') {
        b->sign = s[i] == '-' ? -1 : 1;
        i += 1;
    }

    // detecting when the digits end and/or catching a parse error
    int start = -1;
    bool seen_digits = false;
    while (s[i] != '\0') {
        if (s[i] >= '0' && s[i] <= '9') {
            // skipping leading zeros
            if (s[i] != '0') {
                seen_digits = true;
                if (start == -1) {
                    start = i;
                }
            }
        } else if (seen_digits) {
            break;
        } else  {
            return make_bignum_zero(b);
        }
        i += 1;
    }

    if (start == -1) {
        return make_bignum_zero(b);
    }

    // parsing the digits
    int end = i - 1;
    int tmp = 0;
    int mult = 1;
    int nchars = 0;

    while (end >= start) {
        tmp = tmp + (s[end] - '0') * mult;
        nchars++;
        mult *= 10;
        if (nchars == CHARS_PER_DIGIT) {
            b->digits[b->size++] = tmp;
            tmp = 0;
            mult = 1;
            nchars = 0;
        }
        end -= 1;
    }

    if (tmp) {
        b->digits[b->size++] = tmp;
    }
    return __bignum_cleanup(b);
}

// the buffer is allocated for you, so YOU will need to free it
char* bignum_to_string(bignum* b) {
    char* buf = calloc(CHARS_PER_DIGIT * b->size + 2, sizeof(char));

    // figuring out sign
    int pos = 0;
    if (b->sign == -1) {
        buf[0] = '-';
        pos = 1;
    }

    // writing the unsigned digits to a pre-allocated buffer (in reverse)
    for (int i = 0; i < b->size; i++) {
        int dig = b->digits[i];
        int num_written = 0;
        do {
            buf[pos++] = '0' + (dig % 10);
            dig /= 10;
            num_written += 1;
        } while (dig > 0);

        if (i < b->size - 1) {
            for (int k = num_written; k < CHARS_PER_DIGIT; k++) {
                buf[pos++] = '0';
            }
        }
    }

    // reversing the buffer
    int init = b->sign == -1 ? 1 : 0;
    for (int i = init; i < (pos + init) / 2; i++) {
        char tmp = buf[i];
        buf[i] = buf[pos - i - 1 + init];
        buf[pos - i - 1 + init] = tmp;
    }

    buf[pos] = '\0';
    return buf;
}

bignum* bignum_from_long(long n) {
    bignum* b = alloc_empty_bignum();
    b->size = 0;
    b->sign = n < 0 ? -1 : 1;
    n *= b->sign;

    if (n == 0) {
        b->digits[0] = 0;
        b->size = 1;
    } else {
        while (n > 0) {
            b->digits[b->size++] = n & BASE_MASK;
            n >>= BASE_SHIFT;
        }
    }
    return b;
}

long bignum_to_long(bignum* b) {
    // This function does not test for overflow. Take care with the results
    long result = 0;
    for (int i = b->size - 1; i >= 0; i--) {
        result = (long)b->digits[i] + (result << BASE_SHIFT);
    }
    return result * b->sign;
}


/* Comparison */
// returns -1 if a < b | 0 if a == b | 1 if a > b
int bignum_compare(bignum* a, bignum* b) {
    if (a->sign != b->sign) {
        return a->sign;
    }

    if (a->size > b->size) {
        return a->sign;
    } else if (a->size < b->size) {
        return -a->sign;
    }

    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) {
            return a->sign;
        } else if (a->digits[i] < b->digits[i]) {
            return -a->sign;
        }
    }
    return 0;
}


/* Arithmetic */
bignum* bignum_sub(bignum* a, bignum* b);

bignum* __bignum_shift(bignum* b, int shift) {
    // IN PLACE. right shift is negative `shift`. left shift is positive `shift`
    int new_size = 0;
    if (shift < 0) {
        for (int i = -shift; i < b->size; i++) {
            b->digits[new_size++] = b->digits[i];
        }
    } else {
        for (int i = b->size - 1; i >= 0; i--) {
            if (i + shift < MAX_DIGITS) {
                b->digits[i + shift] = b->digits[i];
            }
        }
        for (int i = 0; i < shift; i++) {
            b->digits[i] = 0;
        }
        new_size = MIN(MAX_DIGITS, b->size + shift);
    }
    b->size = new_size;
    return __bignum_cleanup(b);
}

bignum* bignum_add(bignum* a, bignum* b) {
    if (a->sign != b->sign) {
        b->sign *= -1;
        bignum* ans = bignum_sub(a, b);
        b->sign *= -1;
        return ans;
    }

    int lim = MIN(1 + MAX(a->size, b->size), MAX_DIGITS);
    bignum* result = alloc_empty_bignum();
    result->size = lim;
    result->sign = a->sign;


    int carry = 0;
    for (int i = 0; i < lim; i++) {
        int n = a->digits[i] + b->digits[i] + carry;
        result->digits[i] = n & BASE_MASK;
        carry = n >> BASE_SHIFT;
    }

    return __bignum_cleanup(result);
}

bignum* bignum_sub(bignum* a, bignum* b) {
    if (a->sign != b->sign) {
        b->sign *= -1;
        bignum* ans = bignum_add(a, b);
        b->sign *= -1;
        return ans;
    }

    bool swapped = bignum_compare(a, b) == -a->sign;
    if (swapped) {
        bignum* tmp = b;
        b = a;
        a = tmp;
        a->sign *= -1;
    }

    int lim = MIN(MAX(a->size, b->size), MAX_DIGITS);
    bignum* result = alloc_empty_bignum();
    result->size = lim;
    result->sign = a->sign;

    bool borrow_flag = false;
    for (int i = 0; i < lim; i++) {
        int adigit = a->digits[i];
        int bdigit = b->digits[i];
        if (borrow_flag) {
            adigit -= 1;
        }
        if (adigit >= bdigit) {
            result->digits[i] = adigit - bdigit;
            borrow_flag = false;
        } else {
            result->digits[i] = BASE + adigit - bdigit;
            borrow_flag = true;
        }
    }

    if (swapped) {
        a->sign *= -1;
    }
    return __bignum_cleanup(result);
}


bignum* __bignum_basic_mult(bignum* a, bignum* b) {
    int lim = MIN(a->size + b->size, MAX_DIGITS);
    bignum* result = alloc_empty_bignum();
    result->size = lim;
    result->sign = a->sign * b->sign;

    for (int i = 0; i < a->size; i++) {
        int carry = 0;
        for (int j = 0; j < b->size; j++) {
            long tmp = result->digits[i + j] + carry;
            tmp += (long) a->digits[i] * b->digits[j];
            carry = tmp >> BASE_SHIFT;
            result->digits[i + j] = tmp & BASE_MASK;
        }
        result->digits[i + b->size] += carry;
    }
    return __bignum_cleanup(result);
}

typedef struct {
    bignum low;
    bignum high;
} __karatsuba_split;

__karatsuba_split __karatusba_split_helper(bignum* b, int s) {
    s = MIN(s, b->size);
    __karatsuba_split res = {.low = __BIGNUM_ZERO, .high = __BIGNUM_ZERO};
    res.low.size = res.high.size = 0;

    for (int i = 0; i < s; i++) {
        res.low.digits[res.low.size++] = b->digits[i];
    }
    for (int i = s; i < b->size; i++) {
        res.high.digits[res.high.size++] = b->digits[i];
    }
    __bignum_cleanup(&res.low);
    __bignum_cleanup(&res.high);
    return res;
}

bignum* __bignum_karatsuba_mult(bignum* a, bignum* b) {
    if (a->size < KARATSUBA_CUTOFF || b->size < KARATSUBA_CUTOFF) {
        return __bignum_basic_mult(a, b);
    }
    int m = MAX(a->size, b->size);
    int m2 = m / 2;
    __karatsuba_split asplit = __karatusba_split_helper(a, m2);
    __karatsuba_split bsplit = __karatusba_split_helper(b, m2);
    bignum* z0 = __bignum_karatsuba_mult(&asplit.low, &bsplit.low);
    bignum* z1 = __bignum_karatsuba_mult(bignum_add(&asplit.low, &asplit.high),
                                         bignum_add(&bsplit.low, &bsplit.high));
    bignum* z2 = __bignum_karatsuba_mult(&asplit.high, &bsplit.high);

    bignum* tmp = bignum_sub(z1, bignum_add(z2, z0));
    bignum* tmp2 = bignum_add(__bignum_shift(z2, 2 * m2),
                              __bignum_shift(tmp, m2));
    bignum_free(tmp);
    bignum* result = __bignum_cleanup(bignum_add(tmp2, z0));
    bignum_free(z0);
    bignum_free(z1);
    bignum_free(z2);
    bignum_free(tmp);
    bignum_free(tmp2);
    return result;
}

bignum* bignum_mult(bignum* a, bignum* b) {
    if (a->size < b->size) {
        bignum* tmp = a;
        a = b;
        b = tmp;
    }
    return __bignum_basic_mult(a, b);
    bignum* res;
    if (a->size < KARATSUBA_CUTOFF) {
        res =  __bignum_basic_mult(a, b);
    } else {
        res = __bignum_karatsuba_mult(a, b);
    }
    res->sign = a->sign * b->sign;
    return res;
}

void __bignum_long_div(bignum* n, unsigned d, bignum* q, bignum* r) {
    long remainder = 0;
    long tmp;

    q->size = n->size;
    for (int i = n->size - 1; i >= 0; i--) {
        remainder = (remainder << BASE_SHIFT) | n->digits[i];
        q->digits[i] = tmp = remainder / d;
        remainder -= tmp * d;
    }
    r->digits[0] = remainder;
    r->size = 1;
}

unsigned bits_in_digit(unsigned d) {
    unsigned k = 0;
    while (d > 0) {
        d /= 10;
        k++;
    }
    return k;
}


unsigned v_lshift(bignum* a, int d) {
    unsigned carry = 0;
    for (int i = 0; i < a->size; i++) {
        long acc = (long) (a->digits[i] << d) + carry;
        a->digits[i] = acc & BASE_MASK;
        carry = acc >> BASE_SHIFT;
    }
    return carry;
}

unsigned v_rshift(bignum* a, int size, int d) {
    unsigned carry = 0;
    unsigned shift_mask = (1 << d) - 1;
    a->size = size;
    for (int i = size - 1; i >= 0; i--) {
        unsigned long acc = ((unsigned long)carry << BASE_SHIFT) | a->digits[i];
        carry = acc & shift_mask;
        a->digits[i] = (unsigned int) (acc >> d);
    }
    return carry;
}


#define Py_ARITHMETIC_RIGHT_SHIFT(I, J) \
    ((I) < 0 ? -1-((-1-(I)) >> (J)) : (I) >> (J))

// https://github.com/python/cpython/blob/master/Objects/longobject.c#L2611
void __bignum_div_mod(bignum* v1, bignum* w1, bignum* quotient, bignum* prem) {
    bignum *v, *w, *a;

    size_t i, k;
    int d;
    unsigned int wm1, wm2, carry, q, r, vtop, *v0, *vk, *w0, *ak;
    unsigned long vv;
    signed int zhi;
    signed long z;



    /* allocate space; w will also be used to hold the final remainder */
    v = bignum_copy(v1);
    w = bignum_copy(w1);
    assert(v->size >= w->size && w->size >= 2);

    /* normalize: shift w1 left so that its top digit is >= PyLong_BASE/2.
       shift v1 left by the same amount.  Results go into w and v. */
    d = CHARS_PER_DIGIT - bits_in_digit(w1->digits[w1->size - 1]);
    carry = v_lshift(w, d);
    assert(carry == 0);
    carry = v_lshift(v, d);
    if (carry != 0 || v->digits[v->size - 1] >= w->digits[w->size - 1]) {
        // fprintf(stderr, "carrying!!!: %d\n", carry);
        v->digits[v->size++] = carry;
    }

    /* Now v->ob_digit[size_v-1] < w->ob_digit[size_w-1], so quotient has
       at most (and usually exactly) k = size_v - size_w digits. */
    k = v->size - w->size;
    assert(k >= 0);
    a = alloc_empty_bignum();
    a->size = k;

    v0 = &v->digits[0];
    w0 = &w->digits[0];
    wm1 = w0[w->size - 1];
    wm2 = w0[w->size - 2];

    for (vk = v0 + k, ak = &a->digits[0] + k; vk-- > v0;) {
        // fprintf(stderr, "v = %s\n", bignum_to_string(v));

        /* inner loop: divide vk[0:w->size+1] by w0[0:w->size], giving
           single-digit quotient q, remainder in vk[0:w->size]. */

        /* estimate quotient digit q; may overestimate by 1 (rare) */
        vtop = vk[w->size];
        assert(vtop <= wm1);
        vv = ((unsigned long)vtop << BASE_SHIFT) | vk[w->size-1];
        // fprintf(stderr, "error?... %li | %li ...", vv, wm1);
        q = (unsigned int)(vv / wm1);
        r = (unsigned int)(vv - (long)wm1 * q); /* r = vv % wm1 */
        while ((unsigned long)wm2 * q > (((unsigned long)r << BASE_SHIFT) | vk[w->size-2])) {
            --q;
            r += wm1;
            if (r >= BASE) {
                break;
            }
        }
        assert(q <= BASE);



        /* subtract q*w0[0:w->size] from vk[0:w->size+1] */
        zhi = 0;
        for (i = 0; i < w->size; ++i) {
            // fprintf(stderr, "    inner loop 1 start |  v = %s\n", bignum_to_string(v));

            /* invariants: -PyLong_BASE <= -q <= zhi <= 0;
               -PyLong_BASE * q <= z < PyLong_BASE */
            z = (signed int)vk[i] + zhi - (signed long)q * (signed long)w0[i];
            // fprintf(stderr, "        innner loop | z = %li\n", z);
            vk[i] = (signed int)(z & BASE_MASK);
            // fprintf(stderr, "wtf... %d is equal to %d\n", vk[i] < 0, ((signed int)(z % BASE)) < 0 );
            if ((signed int)vk[i] < 0) {
                // fprintf(stderr, "trying to correct %d\n", vk[i]);
                vk[i] += BASE;
            }
            zhi = (signed int)Py_ARITHMETIC_RIGHT_SHIFT(z, BASE_SHIFT);

            // fprintf(stderr, "    inner loop 1 done | v = %s\n", bignum_to_string(v));
        }

        // fprintf(stderr, "DEBUG 1: %s\n", bignum_to_string(a));
        // fprintf(stderr, "vtop: %li | zhi: %li\n", (long)vtop, (long)zhi);
        /* add w back if q was too large (this branch taken rarely) */
        assert((signed int)vtop + zhi == -1 || (signed int)vtop + zhi == 0);
        if ((signed int)vtop + zhi < 0) {
            fprintf(stderr, "taking rare branch\n");
            carry = 0;
            for (i = 0; i < w->size; ++i) {
                carry += vk[i] + w0[i];
                vk[i] = carry & BASE_MASK;
                carry >>= BASE_SHIFT;
            }
            --q;
        }


        /* store quotient digit */
        assert(q < BASE);
        *--ak = q;
    }

    /* unshift remainder; we reuse w to store the result */
    carry = v_rshift(v, w->size, d);

    assert(carry == 0);
    *prem = *v;
    *quotient = *a;
    bignum_free(v);
    bignum_free(w);
    bignum_free(a);

    __bignum_cleanup(prem);
    __bignum_cleanup(quotient);
}

void bignum_div_mod(bignum* n, bignum* d, bignum* q, bignum* r) {
    // checking if the denominator is 0
    if (d->size == 1 && d->digits[0] == 0) {
        fprintf(stderr, "Error: bignum divison by 0\n");
        abort();
    }

    int n_sign = n->sign;
    int d_sign = d->sign;
    n->sign = d->sign = 1;

    // checking if |d| > |n|
    if (bignum_compare(n, d) < 0) {
        make_bignum_zero(q);
        *r = *n;
    } else if (d->size == 1) {
        __bignum_long_div(n, d->digits[0], q, r);
    } else {
        __bignum_div_mod(n, d, q, r);
    }

    // returning signs to the original values
    n->sign = n_sign;
    d->sign = d_sign;
    q->sign = n_sign * d_sign;
    r->sign = n_sign;
    __bignum_cleanup(q);
    __bignum_cleanup(r);
}

bignum* bignum_div(bignum* n, bignum* d) {
    bignum* quotient = alloc_empty_bignum();
    bignum* remainder = alloc_empty_bignum();
    bignum_div_mod(n, d, quotient, remainder);
    bignum_free(remainder);
    return quotient;
}


bignum* bignum_mod(bignum* n, bignum* d) {
    bignum* quotient = alloc_empty_bignum();
    bignum* remainder = alloc_empty_bignum();
    bignum_div_mod(n, d, quotient, remainder);
    bignum_free(quotient);
    return remainder;
}

bignum* bignum_mod_exp(bignum* base, bignum* exp, bignum* modulus) {
    // provide a `modulus` of NULL to be regular exponentiation
    bool should_mod = modulus != NULL;

    bignum* tmp;
    bignum* result = alloc_empty_bignum();
    result->digits[0] = 1;
    result->size = 1;
    result->sign = 1;

    exp = bignum_copy(exp);
    if (should_mod) {
        base = bignum_mod(base, modulus);
    } else {
        base = bignum_copy(base);
    }

    while (bignum_compare(exp, BIGNUM_ZERO) > 0) {
        if (exp->digits[0] % 2 == 1) {
            tmp = bignum_mult(result, base);
            bignum_free(result);
            result = tmp;

            if (should_mod) {
                tmp = bignum_mod(result, modulus);
                bignum_free(result);
                result = tmp;
            }
        }

        tmp = bignum_div(exp, BIGNUM_TWO);
        bignum_free(exp);
        exp = tmp;

        tmp = bignum_mult(base, base);
        bignum_free(base);
        base = tmp;

        if (should_mod) {
            tmp = bignum_mod(base, modulus);
            bignum_free(base);
            base = tmp;
        }
    }

    bignum_free(base);
    bignum_free(exp);

    return __bignum_cleanup(result);
}
