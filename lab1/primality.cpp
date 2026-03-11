#include "primality.h"

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 0;
    a %= m;

    while (b > 0) {
        if (b & 1) {
            result = (result + a) % m;
        }

        a = (a * 2) % m;
        b >>= 1;
    }

    return result;
}

uint64_t pow_mod(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 1;
    a %= m;

    while (b > 0) {
        if (b & 1){
            result = mul_mod(result, a, m);
        }

        a = mul_mod(a, a, m);
        b >>= 1;
    }

    return result;
}

