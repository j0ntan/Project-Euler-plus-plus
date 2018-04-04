/* Pandigital products
 * We shall say that an n-digit number is pandigital if it makes
 * use of all the digits 1 to n exactly once; for example, the
 * 5-digit number, 15234, is 1 through 5 pandigital.
 *
 * The product 7254 is unusual, as the identity, 39 × 186 = 7254,
 * containing multiplicand, multiplier, and product is 1 through
 * 9 pandigital.
 *
 * Find the sum of all products whose multiplicand/multiplier/
 * product identity can be written as a 1 through 9 pandigital.
 *
 * HINT: Some products can be obtained in more than one way so
 * be sure to only include it once in your sum. */

#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <algorithm>
#include "../../utils/utils.h"

unsigned totalDigitCount(unsigned multiplicand, unsigned multiplier, unsigned product);

bool combinedIsPalindrome(unsigned multiplicand, unsigned multiplier, unsigned product);

int main() {
    std::set<unsigned> panProd;

    auto multiplicand = 1u;
    auto multiplier = 1u;
    auto product = 0u;
    auto digitCount = 0u;
    do {
        do {
            product = multiplicand * multiplier;
            digitCount = totalDigitCount( multiplicand
                    ,multiplier,product );
            if( digitCount==9 && combinedIsPalindrome(
                    multiplicand,multiplier,product ) )
                panProd.insert(product);
            ++multiplier;
        } while( digitCount<10 );

        ++multiplicand;
        multiplier = 1;
        digitCount = 2 * projEuler::getDigits(
                multiplicand).size() + 1;
    } while( digitCount<10 );

    auto &p = panProd;
    std::cout << "result: "
              << std::accumulate(p.begin(),p.end(),0u)
              << std::endl;
}

bool combinedIsPalindrome(unsigned multiplicand
        , unsigned multiplier, unsigned product) {
    using namespace projEuler;
    std::vector<unsigned> combined;
    auto n1 = getDigits(multiplicand);
    auto n2 = getDigits(multiplier);
    auto n3 = getDigits(product);

    combined.insert( combined.end(),n1.begin(),n1.end() );
    combined.insert( combined.end(),n2.begin(),n2.end() );
    combined.insert( combined.end(),n3.begin(),n3.end() );

    for( auto i=1u; i<=9; ++i )
        if( std::find(combined.begin()
                ,combined.end(),i) == combined.end() )
            return false;

    return true;
}

unsigned totalDigitCount(unsigned multiplicand
        , unsigned multiplier, unsigned product) {
    using namespace projEuler;
    return getDigits(multiplicand).size()
           + getDigits(multiplier).size()
           + getDigits(product).size();
}
