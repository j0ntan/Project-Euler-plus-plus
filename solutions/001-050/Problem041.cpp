/* Pandigital prime
 * We shall say that an n-digit number is pandigital if it
 * makes use of all the digits 1 to n exactly once. For
 * example, 2143 is a 4-digit pandigital and is also prime.
 *
 * What is the largest n-digit pandigital prime that exists? */

#include <iostream>
#include <algorithm>
#include "../../utils/utils.h"

int main() {
    unsigned result = 0;

    // begin with 9-digit pandigital
    auto digits = projEuler::getDigits(123456789u);
    while( result==0 ) {
        using namespace projEuler;

        auto reps = factorial( digits.size() );
        for( auto i=0u; i<reps; ++i ) {
            std::next_permutation(digits.begin(),digits.end());

            unsigned num = combineDigits(digits);
            if( isPrime(num) && num>result )
                result = num;
        }
        digits.pop_back();
    }

    std::cout << "result: " << result << std::endl;
}
