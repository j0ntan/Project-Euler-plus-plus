/* Circular primes
 * The number, 197, is called a circular prime because
 * all rotations of the digits: 197, 971, and 719, are
 * themselves prime.
 *
 * There are thirteen such primes below
 * 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79,
 * and 97.
 *
 * How many circular primes are there below one
 * million? */

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../utils/utils.h"

bool isCircPrime(unsigned num);

int main() {
    auto limit = static_cast<unsigned>( 1e6 );
    std::vector<unsigned> circularPrimes;

    for( auto i=2u; i<limit; ++i ) {
        if( isCircPrime(i) )
            circularPrimes.push_back(i);
    }

    std::cout << "result: "
              << circularPrimes.size()
              << std::endl;
}

bool isCircPrime(unsigned num) {
    using namespace projEuler;

    auto digits = getDigits(num);
    for( auto i=0u; i<digits.size(); ++i ) {
        if( !isPrime(num) )
            return false;
        if( digits.size()>1 ) {
            std::rotate(digits.begin(),
                        digits.begin()+1,
                        digits.end());
            num = combineDigits( digits );
        }
    }
    return true;
}