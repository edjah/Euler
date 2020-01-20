/*
B(n) can be computed recursively.
    - fixed +1 guess
    - let a = floor((n - 1)/2)   and   b = (n - 1) - a
    - 1/n probability that the guess is correct and 0 more guesses are required
    - a/n probability that we have B(a) more guesses
    - b/n probability that we have B(b) more guesses

R(n) can also be computed recursively.
    - 1/n probability that random guess is correct
    - so we can iterate over all possible guesses and weight them
            ans = 0
            for a in range(0, n):
                b = (n - 1) - a
                ans += (a*R(a) + b*R(b)) / (n ** 2)

    - If you expand out the recursion, it turns out the R(n + 1) is just:
             2 * (1*R(1) + 2*R(2) + ... + (n-1)*R(n-1))
        1 + --------------------------------------
                             n * n

    - So we can compute R(n) in O(n) time by keeping track of the cumsum
*/

#include "lib/utility.hh"

using namespace std;

unordered_map<long, double> B_cache;

double B(long n) {
    if (n <= 1) {
        return 1;
    } else if (B_cache.count(n)) {
        return B_cache[n];
    }

    long a = (n - 1) / 2;
    long b = (n - 1) - a;
    double ans = 1.0 + (a*B(a) + b*B(b)) / n;

    B_cache[n] = ans;
    return ans;
}


double R(long n) {
    double sum = 1;
    double ri = 0.0;

    for (double i = 2; i <= n; ++i) {
        ri = 1 + 2 * sum / (i * i);
        sum += i * ri;
    }

    return ri;
}


int main() {
    start_time();
    printf("Solution: %.8f\n", R(1e10) - B(1e10));
    end_time();
}
