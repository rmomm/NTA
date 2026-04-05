#include "factorization.h"
#include "primality.h"

uint64_t trialDivision(uint64_t n) {
 
    vector<uint64_t> primes = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47 };

    for (uint64_t p : primes) {
        if (n % p == 0) 
        {
            cout << "Found divisor: " << p;
            return p;
        }
    }

    return 0; 
}

uint64_t f(uint64_t x, uint64_t n) {
    return (mul_mod(x, x, n) + 1) % n;
}

uint64_t pollardRho(uint64_t n) {
    if (n % 2 == 0) { 
        return 2; 
    }

    uint64_t x = 2;
    uint64_t y = 2;
    uint64_t d = 1;

    while (d == 1) {
        x = f(x, n);
        y = f(f(y, n), n);

        uint64_t diff = (x > y) ? (x - y) : (y - x);
        d = gcd(diff, n);

        if (d == n) { 
            return 0; 
        }
    }

    return d;
}



