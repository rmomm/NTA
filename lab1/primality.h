#pragma once
#include <cstdint>
#include <algorithm>
#include <random>
using namespace std;

uint64_t gcd(uint64_t a, uint64_t b);
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod);
uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod);
//int jacobi(uint64_t a, uint64_t n);
//bool solovayStrassen(uint64_t p, int k);
