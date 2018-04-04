/* Truncatable primes
 * The number 3797 has an interesting property. Being prime
 * itself, it is possible to continuously remove digits from
 * left to right, and remain prime at each stage:
 * 3797, 797, 97, and 7. Similarly we can work from right to
 * left: 3797, 379, 37, and 3.
 *
 * Find the sum of the only eleven primes that are both
 * truncatable from left to right and right to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable
 * primes. */

#include <iostream>
#include <vector>
#include <numeric>
#include <list>
#include "../../utils/utils.h"

bool truncLeftPrime(unsigned num);

bool truncRightPrime(unsigned num);

int main() {
    std::vector<unsigned> truncPrimes;
    auto primeCount = 0u;

    // Start at 11 due to NOTE from
    // problem description
    auto num = 11u;
    while( primeCount<11 ) {
        if( projEuler::isPrime(num)
                && truncRightPrime(num)
                && truncLeftPrime(num) ) {
            truncPrimes.push_back(num);
            ++primeCount;
        }
        ++num;
    }

    auto &tp = truncPrimes;
    std::cout << "result: "
              << std::accumulate(tp.begin(),tp.end(),0u)
              << std::endl;
}

bool truncRightPrime(unsigned num) {
    using namespace projEuler;

    auto digits = getDigits(num);
    digits.pop_back();

    while( digits.size()>0 ) {
        if( !isPrime(num) )
            return false;

        digits.pop_back();
        num = combineDigits(digits);
    }

    return true;
}

bool truncLeftPrime(unsigned num) {
    using namespace projEuler;

    auto vec_digits = getDigits(num);
    std::list<unsigned> digits( vec_digits.begin() + 1
            ,vec_digits.end() );

    while( digits.size()>0 ) {
        vec_digits.clear();
        std::copy( digits.begin(),digits.end()
                ,std::back_inserter(vec_digits) );
        num = combineDigits(vec_digits);

        if (!isPrime(num))
            return false;
        digits.pop_front();
    }

    return true;
}