#pragma once
#include <cstdint>
#include <algorithm>
#include <random>
#include <cstdlib>
using namespace std;

uint64_t gcd(uint64_t a, uint64_t b);
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod);
uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod);
bool millerTest(uint64_t n, uint64_t d, uint64_t s);
bool isPrime(uint64_t n, int k);