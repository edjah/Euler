#define MAX_DIGITS 128
#include "bignum.h"

int main(void) {
    // char* s1 = "12301391232119321302193128739218391232193219731231233333333219309999999999000000000000921031293333333333333333333333333332222222222222222222222222222222222222222223229219231312123912312312312312312832321312123013912321312312333333333333333333333333333333333322222222222222222222222222222222222222222232292192313121239123123123123123128323213121230139123213123123333333333333333333333333333333333222222222222222222222222222222222222222222322921923131212391231231231231231283232131212301391232131231233333333333333333333333333333333332222222222222222222222222222222222222222223229219231312123912312312312312312832321312";
    // char* s2 = "12301391232131231233333333333333333333333333333333332222222222222222222222222222222222222222223229219231312123912312312312312312831231321";
    // char* ans = "151324226245955131310199647236602187777777777777777750441352817486152814814814814814814814814839589743172851163535413505117369924745558526522945903422074338581227284511500689923255435558803580184899552597470267490179613454714640615334248161987588127604944688942738917668737265229459034220743385812272845115006899232554355588035801848995525974702674901796134547146406153342481619875881276049446889427389176687372652294590342207433858122728451150068992325543555880358018489955259747026749017961345471464061533424816198758812760494468894273891766873725009703640962523025479230812145478812145477657781026075771371377735942119342031465306566492466938350730259076492250809637769039670213152";
    // bignum* a = bignum_from_string(s1);
    // bignum* b = bignum_from_string(s2);

    // printf("%s\n\n\n", bignum_to_string(a));
    // printf("%s\n", bignum_to_string(b));
    // bignum* c = bignum_mult(a, b);
    // fprintf(stderr, "\nObserved: %s\n\nExpected: %s\n\n", bignum_to_string(c), ans);
    // assert(strcmp(bignum_to_string(c), ans) == 0);

    // bignum res = BIGNUM_ZERO;
    // bignum z;
    // start_time();
    // for (long i = -500000; i < 500000; i++) {
    //     long x = (long) (rand() - rand());
    //     long y = (long) (rand() - rand());

    //     bignum b = bignum_mult(bignum_from_long(x), bignum_from_long(y));
    //     assert(bignum_to_long(b) == x * y);
    // }

    for (long i = -10000; i < 10000; i++) {
        long j = i * (BASE - 312917111) * 312901 + 1;
        char buf[300];
        sprintf(buf, "%li", j);

        bignum* a = bignum_from_long(j);
        bignum* b = bignum_from_string(buf);

        bignum* c = bignum_mult(bignum_from_long(i), a);
        long div_res = bignum_to_long(bignum_div(c, a));
        if (div_res != i) {
            fprintf(stderr, "%s / %s\n\nGot: %li\nExpected: %li\n",
                    bignum_to_string(c), bignum_to_string(a), div_res, i);
            // assert(div_res == i);
            return 0;
        }

        char* s1 = bignum_to_string(a);
        char* s2 = bignum_to_string(b);

        if (strcmp(s1, buf) != 0|| strcmp(s2, buf) != 0) {
            fprintf(stderr, "s1  = %s\ns2  = %s\nbuf = %s\n", s1, s2, buf);
            assert(strcmp(s1, buf) == 0);
            assert(strcmp(s2, buf) == 0);
        }

        free(s1);
        free(s2);
        bignum_free(a);
        bignum_free(b);
    }

    end_time();
}