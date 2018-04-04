/* Sub-string divisibility
 * The number, 1406357289, is a 0 to 9 pandigital number
 * because it is made up of each of the digits 0 to 9 in
 * some order, but it also has a rather interesting
 * sub-string divisibility property.
 *
 * Let d1 be the 1st digit, d2 be the 2nd digit, and so on.
 * In this way, we note the following:
 *
 *      d2d3d4=406 is divisible by 2
 *      d3d4d5=063 is divisible by 3
 *      d4d5d6=635 is divisible by 5
 *      d5d6d7=357 is divisible by 7
 *      d6d7d8=572 is divisible by 11
 *      d7d8d9=728 is divisible by 13
 *      d8d9d10=289 is divisible by 17
 *
 * Find the sum of all 0 to 9 pandigital numbers with this
 * property. */

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../utils/utils.h"

bool hasDivisibilityProperty(long long num);

int main() {
    using namespace projEuler;
    std::vector<long long> divNums;
    const auto reps = factorial(10u);
    std::vector<long long>digits = {0,1,2,3,4,5,6,7,8,9};

    for( auto i=0u; i<reps; ++i ) {
        auto num = combineDigits(digits);
        if( digits[0] != 0 && hasDivisibilityProperty(num) )
            divNums.push_back(num);
        std::next_permutation(digits.begin(),digits.end());
    }

    std::cout << "result: "
              << std::accumulate(divNums.begin()
                      ,divNums.end(),0LL)
              << std::endl;
}

bool hasDivisibilityProperty(long long num) {
    using namespace projEuler;

    auto digits = getDigits(num);
    auto it = digits.begin();

    return combineDigits(
           std::vector<long long>(it+1,it+4))
           %2==0 &&
           combineDigits(
           std::vector<long long>(it+2,it+5))
           %3==0 &&
           combineDigits(
           std::vector<long long>(it+3,it+6))
           %5==0 &&
           combineDigits(
           std::vector<long long>(it+4,it+7))
           %7==0 &&
           combineDigits(
           std::vector<long long>(it+5,it+8))
           %11==0 &&
           combineDigits(
           std::vector<long long>(it+6,it+9))
           %13==0 &&
           combineDigits(
           std::vector<long long>(it+7,it+10))
           %17==0;
}
