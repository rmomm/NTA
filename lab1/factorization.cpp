#include "factorization.h"

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



