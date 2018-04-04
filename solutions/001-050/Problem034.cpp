/* Digit factorials
 * 145 is a curious number, as 1! + 4! + 5! =
 * 1 + 24 + 120 = 145.
 *
 * Find the sum of all numbers which are equal to the sum  of
 * the factorial of their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included. */

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../utils/utils.h"

void findValidNums(std::vector<unsigned> &validNums);

int main() {
    std::vector<unsigned> validNums;

    findValidNums(validNums);

    std::cout << "result: "
              << std::accumulate(validNums.begin(),validNums.end(),0u)
              << std::endl;
}

std::vector<unsigned> digitFactorials(const std::vector<unsigned> &digits) {
    std::vector<unsigned> v(digits.size());
    for( auto i=0; i<digits.size(); ++i )
        v[i] = projEuler::factorial(digits[i]);
    return v;
}

void findValidNums(std::vector<unsigned> &validNums) {
    using namespace projEuler;

    unsigned num=10;
    const unsigned limit = 362880; // value of !9
    do {
        auto digits = getDigits(num);
        auto factorials = digitFactorials(digits);

        auto factorialSum = std::accumulate(factorials.begin(),
                                            factorials.end(),0u);

        if( num==factorialSum )
            validNums.push_back(num);
    } while( ++num <= limit );
}