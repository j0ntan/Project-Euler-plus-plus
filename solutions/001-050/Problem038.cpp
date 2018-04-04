/* Pandigital multiples
 * Take the number 192 and multiply it by each of 1, 2,
 * and 3:
 *
 *  192 × 1 = 192
 *  192 × 2 = 384
 *  192 × 3 = 576
 *
 * By concatenating each product we get the 1 to 9 pandigital,
 * 192384576. We will call 192384576 the concatenated product
 * of 192 and (1,2,3)
 *
 * The same can be achieved by starting with 9 and multiplying
 * by 1, 2, 3, 4, and 5, giving the pandigital, 918273645,
 * which is the concatenated product of 9 and (1,2,3,4,5).
 *
 * What is the largest 1 to 9 pandigital 9-digit number that
 * can be formed as the concatenated product of an integer
 * with (1,2, ... , n) where n > 1? */

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../utils/utils.h"

unsigned concatMultiply(unsigned num, const std::vector<unsigned> &vec);

bool isPandigital(unsigned product);

int main() {
    /* The problem description does not give a name
     * for the structure (1,2,...,n). In this program,
     * we can just call it the multiplier. So in the
     * following equation, 192 x (1,2,3) = 192384576,
     * we have 192 as the multiplicand, (1,2,3) as the
     * multiplier, and 192384576 as the concatenated
     * product ('concatProd'). */

    // bounds for pandigital
    // concatenated products
    const unsigned upperLimit = 987654321;
    const unsigned lowerLimit = 123456789;

    unsigned maxConcatProd = 0;

    unsigned multiplicand = 1;
    unsigned product = 0;
    do {
        std::vector<unsigned> multiplier {1,2};
        do {
            product = concatMultiply(multiplicand
                    ,multiplier);

            if( product >= lowerLimit
                    && isPandigital(product)
                    && product > maxConcatProd )
                maxConcatProd = product;

            multiplier.push_back( multiplier.back()+1 );
        } while( product<upperLimit );
        ++multiplicand;
        product = concatMultiply(multiplicand
                ,std::vector<unsigned>{1,2});
    } while( product<upperLimit );

    std::cout << "result: " << maxConcatProd << std::endl;
}

bool isPandigital(unsigned product) {
    auto digits = projEuler::getDigits(product);

    if( digits.size()!=9 )
        return false;
    else
        for( auto i=1u; i<10; ++i ) {
            auto it = std::find( digits.begin()
                    ,digits.end(), i );
            if( it==digits.end() )
                return false;
        }

    return true;
}

unsigned concat(unsigned num1, unsigned num2) {
    auto digits1 = projEuler::getDigits(num1);
    auto digits2 = projEuler::getDigits(num2);
    digits1.insert( digits1.end()
            ,digits2.begin(),digits2.end() );
    return projEuler::combineDigits(digits1);
}

unsigned concatMultiply(unsigned num, const std::vector<unsigned> &vec) {
    unsigned product = 0;
    for( auto i=0u; i<vec.size(); ++i )
        product = concat( product, num*vec[i] );
    return product;
}
