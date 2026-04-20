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
        if (b & 1) {
            result = mul_mod(result, a, m);
        }

        a = mul_mod(a, a, m);
        b >>= 1;
    }

    return result;
}


bool millerTest(uint64_t n, uint64_t d, uint64_t s) {
    uint64_t a = 2 + rand() % (n - 3);

    if (gcd(a, n) > 1) {
        return false;
    }

    uint64_t x = pow_mod(a, d, n);

    if (x == 1 || x == n - 1) {
        return true;
    }

    for (uint64_t r = 1; r < s; r++) {
        x = mul_mod(x, x, n);

        if (x == n - 1) {
            return true;
        }
        if (x == 1) {
            return false; 
        }
    }

    return false;
}

bool isPrime(uint64_t n, int k) {
    if (n < 2) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    uint64_t d = n - 1;
    uint64_t s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < k; i++) {
        if (!millerTest(n, d, s)) {
            return false;
        }
    }

    return true;
}