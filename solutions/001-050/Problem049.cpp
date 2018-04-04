/* Prime permutations
 * The arithmetic sequence, 1487, 4817, 8147, in which each
 * of the terms increases by 3330, is unusual in two ways:
 * (i) each of the three terms are prime, and, (ii) each of
 * the 4-digit numbers are permutations of one another.
 *
 * There are no arithmetic sequences made up of three 1-, 2-,
 * or 3-digit primes, exhibiting this property, but there is
 * one other 4-digit increasing sequence.
 *
 * What 12-digit number do you form by concatenating the three
 * terms in this sequence? */

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../utils/utils.h"

bool isSeqPrimes(unsigned num);

bool isSeqPermutations(unsigned num);

int main() {
    auto num = 1487u;
    bool foundSequence = false;
    while( !foundSequence && ++num <= 3339 )
        foundSequence = isSeqPrimes(num) &&
                isSeqPermutations(num);

    std::cout << "result: "
              << std::to_string(num)
              << std::to_string(num+3330)
              << std::to_string(num+6660)
              << std::endl;
}

bool isSeqPermutations(unsigned num) {
    auto digits1 = projEuler::getDigits(num);
    auto digits2 = projEuler::getDigits(num+3330);
    auto digits3 = projEuler::getDigits(num+6660);

    return
            std::is_permutation( digits2.begin(), digits2.end()
            , digits1.begin()) &&
            std::is_permutation( digits3.begin(), digits3.end()
            , digits1.begin());
}

bool isSeqPrimes(unsigned num) {
    using projEuler::isPrime;
    return isPrime(num) &&
            isPrime(num+3330) && isPrime(num+6660);
}
