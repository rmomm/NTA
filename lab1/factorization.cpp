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

int legendreSymbol(uint64_t a, uint64_t p) {
    uint64_t res = pow_mod(a, (p - 1) / 2, p);

    if (res == 1) { 
        return 1; 
    }
    if (res == p - 1) { 
        return -1; 
    }
    return 0;
}

vector<uint64_t> factorBase(uint64_t n) {
    vector<uint64_t> B;
    B.push_back(-1); // p0 = -1

    uint64_t L = exp(sqrt(log(n) * log(log(n))));

    for (uint64_t p = 2; p <= L; p++) {
        if (isPrime(p, 5) && legendreSymbol(n, p) == 1) {
            B.push_back(p);
        }
    }

    return B;
}

ContinuedFraction sqrtContinuedFraction(uint64_t n, int s) {
    vector<uint64_t> q(s);
    vector<uint64_t> b(s);

    uint64_t u = 0;
    uint64_t v = 1;

    uint64_t a0 = sqrt(n);
    q[0] = a0;

    b[0] = a0;
    if (s > 1) { 
        b[1] = q[0] * b[0] + 1;
    }

    for (int k = 1; k < s; k++) {
        uint64_t v_next = (n - u * u) / v;
        uint64_t q_next = (a0 + u) / v_next;
        uint64_t u_next = q_next * v_next - u;

        q[k] = q_next;

        if (k >= 2) {
            b[k] = q[k] * b[k - 1] + b[k - 2];
        }

        u = u_next;
        v = v_next;
    }

    return { q, b };
}

vector<int> factorVector(uint64_t bi, vector<uint64_t>& B, uint64_t n) {
    vector<int> v(B.size(), 0);

    uint64_t x = (bi * bi) % n;

    for (int j = 0; j < B.size(); j++) {
        uint64_t p = B[j];

        while (x % p == 0) {
            v[j]++;
            x /= p;
        }

        v[j] %= 2; // mod 2
    }

    if (x != 1) { 
        return {};
    } // не B-гладке

    return v;
}

vector<int> solveGF2(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    for (uint64_t mask = 1; mask < (1ULL << n); mask++) {
        vector<int> sum(m, 0);

        for (int i = 0; i < n; i++) {
            if (mask & (1ULL << i)) {
                for (int j = 0; j < m; j++) {
                    sum[j] = (sum[j] + mat[i][j]) % 2;
                }
            }
        }

        bool zero = true;
        for (int j = 0; j < m; j++) {
            if (sum[j] != 0) { 
                zero = false; 
            }
        }

        if (zero) {
            vector<int> res(n);
            for (int i = 0; i < n; i++) {
                res[i] = (mask >> i) & 1;
            }
            return res;
        }
    }

    return {};
}

uint64_t computeX(vector<int>& x, vector<uint64_t>& bi, uint64_t n) {
    uint64_t X = 1;

    for (int i = 0; i < x.size(); i++) {
        if (x[i]) {
            X = (X * bi[i]) % n;
        }
    }

    return X;
}

uint64_t computeY(vector<int>& x, vector<vector<int>>& vi, vector<uint64_t>& B, uint64_t n) {

    uint64_t Y = 1;

    for (int j = 0; j < B.size(); j++) {
        int sum = 0;

        for (int i = 0; i < x.size(); i++) {
            if (x[i]) { 
                sum += vi[i][j]; 
            }
        }

        for (int k = 0; k < sum / 2; k++) {
            Y = (Y * B[j]) % n;
        }
    }

    return Y;
}

uint64_t brillhartMorrison(uint64_t n) {
    vector<uint64_t> B = factorBase(n);

    ContinuedFraction cf = sqrtContinuedFraction(n, 20);

    vector<vector<int>> matrix;
    vector<uint64_t> good_b;

    for (int i = 0; i < cf.b.size(); i++) {
        vector<int> v = factorVector(cf.b[i], B, n);

        if (!v.empty()) {
            matrix.push_back(v);
            good_b.push_back(cf.b[i]);
        }
    }

    vector<int> sol = solveGF2(matrix);

    if (sol.empty()) { 
        return 0; 
    }

    uint64_t X = computeX(sol, good_b, n);
    uint64_t Y = computeY(sol, matrix, B, n);

    if (X == Y || X == (n - Y)) { 
        return 0; 
    }

    uint64_t d = gcd((X > Y ? X - Y : Y - X), n);

    if (d == 1 || d == n) { 
        return 0; 
    }

    return d;
}