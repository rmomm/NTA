#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>
#include "factorization.h"
#include "primality.h"

using namespace std;
using namespace chrono;

void runFullFactorization(uint64_t n) {
    cout << "\n-----------------------------------\n";
    cout << "Number: " << n << "\n";

    auto startAll = high_resolution_clock::now();


    auto start = high_resolution_clock::now();
    bool prime = isPrime(n, 5);
    auto end = high_resolution_clock::now();
    cout << "\n\n Miller-Rabin \n";
    cout << (prime ? "Prime" : "Composite") << "\n";
    cout << "Time: " << duration_cast<microseconds>(end - start).count() / 1000.0 << " ms\n";
    if (prime) { 
        return; 
    }


    start = high_resolution_clock::now();
    uint64_t td = trialDivision(n);
    end = high_resolution_clock::now();
    cout << "\n\n Trial Division \n";
    if (td) {
        cout << "Divisor: " << td << "\n"; 
    }
    else { 
        cout << "No small factor found\n"; 
    }
    cout << "Time: " << duration_cast<microseconds>(end - start).count() / 1000.0 << " ms\n";


    start = high_resolution_clock::now();
    uint64_t pr = pollardRho(n);
    end = high_resolution_clock::now();
    cout << "\n\n Pollard Rho \n";
    if (pr) { 
        cout << "Divisor: " << pr << "\n"; 
    }
    else { 
        cout << "Not found\n"; 
    }
    cout << "Time: " << duration_cast<microseconds>(end - start).count() / 1000.0 << " ms\n";

    start = high_resolution_clock::now();
    uint64_t bm = brillhartMorrison(n);
    end = high_resolution_clock::now();
    cout << "\n\n Brillhart-Morrison \n";
    if (bm) { 
        cout << "Divisor: " << bm << "\n"; 
    }
    else { 
        cout << "Not found\n"; 
    }
    cout << "Time: " << duration_cast<microseconds>(end - start).count() / 1000.0 << " ms\n";


    vector<uint64_t> factors;
    factor(n, factors);
    cout << "\n\n CANONICAL FACTORIZATION \n";
    printCanonical(n, factors);

    auto endAll = high_resolution_clock::now();
    cout << "Total time: " << duration_cast<microseconds>(endAll - startAll).count() / 1000.0 << " ms\n";
}

void compareAlgorithms(uint64_t n) {
    cout << "\n---------------------------------\n";
    cout << "Number: " << n << "\n";

    auto start = high_resolution_clock::now();
    uint64_t p = pollardRho(n);
    auto end = high_resolution_clock::now();
    cout << "\n POLLARD RHO \n";
    if (p) { 
        cout << "Divisor: " << p << "\n"; 
    }
    else { 
        cout << "Not found\n"; 
    }
    cout << "Time: " << duration_cast<microseconds>(end - start).count() / 1000.0 << " ms\n";

    start = high_resolution_clock::now();
    uint64_t q = brillhartMorrison(n);
    end = high_resolution_clock::now();
    cout << "\n Brillhart-Morrison \n";
    if (q) { 
        cout << "Divisor: " << q << "\n"; 
    }
    else { 
        cout << "Not found\n"; 
    }
    cout << "Time: " << duration_cast<microseconds>(end - start).count() / 1000.0 << " ms\n";
}

int main() {
    runFullFactorization(323324583518541583ULL);

    vector<uint64_t> numbers = {
        3009182572376191ULL,
        1021514194991569ULL,
        4000852962116741ULL,
        15196946347083ULL,
        499664789704823ULL,
        269322119833303ULL,
        679321846483919ULL,
        96267366284849ULL,
        61333127792637ULL,
        2485021628404193ULL
    };

    for (auto n : numbers) {
        compareAlgorithms(n);
    }

    return 0;
}
