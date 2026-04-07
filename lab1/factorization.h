#pragma once
#include <vector>
#include <iostream>
#include <cstdint>
using namespace std;

uint64_t trialDivision(uint64_t n);
uint64_t f(uint64_t x, uint64_t n);
uint64_t pollardRho(uint64_t n);

struct ContinuedFraction {
    vector<uint64_t> q;
    vector<uint64_t> b;
};

int legendreSymbol(uint64_t a, uint64_t p);
vector<uint64_t> factorBase(uint64_t n);

ContinuedFraction sqrtContinuedFraction(uint64_t n, int s);

vector<int> factorVector(uint64_t bi, vector<uint64_t>& B, uint64_t n);

vector<int> solveGF2(vector<vector<int>>& mat);

uint64_t computeX(vector<int>& x, vector<uint64_t>& bi, uint64_t n);
uint64_t computeY(vector<int>& x, vector<vector<int>>& vi, vector<uint64_t>& B, uint64_t n);

uint64_t brillhartMorrison(uint64_t n);