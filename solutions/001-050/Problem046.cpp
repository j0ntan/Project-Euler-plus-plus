/* Goldbach's other conjecture
 * It was proposed by Christian Goldbach that every odd composite
 * number can be written as the sum of a prime and twice a square.
 *
 *  9 = 7 + 2×1^2
 *  15 = 7 + 2×2^2
 *  21 = 3 + 2×3^2
 *  25 = 7 + 2×3^2
 *  27 = 19 + 2×2^2
 *  33 = 31 + 2×1^2
 *
 * It turns out that the conjecture was false.
 *
 * What is the smallest odd composite that cannot be written as the
 * sum of a prime and twice a square? */

#include <iostream>
#include <vector>
#include "../../utils/utils.h"

std::vector<unsigned> createPrimesList(unsigned limit);

bool findComposition(int num
        , const std::vector<unsigned int> &primes);

int main() {
    auto primes = createPrimesList(600u);

    bool validComposite = false;
    auto num = 7;
    do {
        num += 2;
        if( !projEuler::isPrime(num) )
            validComposite = findComposition(num,primes);
    } while(validComposite);

    std::cout << "result: " << num << std::endl;
}

bool findComposition(int num
        , const std::vector<unsigned int> &primes) {
    auto size = primes.size();
    auto i = 0u;
    do {
        auto toBeSquared = 1u;
        auto calculation = 0u;
        do {
            calculation = primes[i] +
                          2*toBeSquared*toBeSquared;
            if( calculation==num )
                return true;
            ++toBeSquared;
        } while( calculation < num );
    } while( primes[++i]<num && i<size );
    return false;
}

std::vector<unsigned> createPrimesList(unsigned limit) {
    std::vector<unsigned> primeNums;
    for( auto i=0u,j=1u; i<limit; ++i ) {
        while( !projEuler::isPrime(++j) );
        primeNums.push_back(j);
    }
    return primeNums;
}