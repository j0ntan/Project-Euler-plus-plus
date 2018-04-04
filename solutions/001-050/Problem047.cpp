/* Distinct primes factors
 * The first two consecutive numbers to have two distinct
 * prime factors are:
 *
 *          14 = 2 × 7
 *          15 = 3 × 5
 *
 * The first three consecutive numbers to have three distinct
 * prime factors are:
 *
 *          644 = 2² × 7 × 23
 *          645 = 3 × 5 × 43
 *          646 = 2 × 17 × 19.
 *
 * Find the first four consecutive integers to have four
 * distinct prime factors each. What is the first of these
 * numbers? */

#include <iostream>
#include <vector>
#include <set>
#include "../../utils/utils.h"

bool hasFourPrimes(unsigned num, const std::vector<unsigned> &primes);

std::vector<unsigned> createPrimesList(unsigned limit);

int main() {
    std::vector<unsigned> primes = createPrimesList(500u);
    auto num = 645u;
    bool foundFourConsecNums = false;
    do {
        if( !projEuler::isPrime(num) &&
                !projEuler::isPrime(num+1) &&
                !projEuler::isPrime(num+2) &&
                !projEuler::isPrime(num+3) ) {
            foundFourConsecNums = hasFourPrimes(num, primes) &&
                    hasFourPrimes(num + 1, primes) &&
                    hasFourPrimes(num + 2, primes) &&
                    hasFourPrimes(num + 3, primes);
        }
        ++num;
    } while(!foundFourConsecNums);
    --num; // undo increment after having found ans.

    std::cout << "result: " << num << std::endl;
}

std::vector<unsigned> createPrimesList(unsigned limit) {
    std::vector<unsigned> primeNums;
    for( auto i=0u,j=1u; i<limit; ++i ) {
        while( !projEuler::isPrime(++j) );
        primeNums.push_back(j);
    }
    return primeNums;
}

bool hasFourPrimes(unsigned num
        , const std::vector<unsigned> &primes) {
    std::set<unsigned> distinctPrimes;
    auto size = primes.size();

    auto i = 0u;
    do {
        i = 0;
        do {
            if( num%primes[i] == 0 ) {
                distinctPrimes.insert(primes[i]);
                num /= primes[i];
                break;
            }
            ++i;
        } while( num > 1 && i < size );
    } while( num > 1 && i < size );

    return distinctPrimes.size()==4;
}