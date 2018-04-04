/* Reciprocal cycles
 * A unit fraction contains 1 in the numerator. The decimal
 * representation of the unit fractions with denominators 2
 * to 10 are given:
 *
 *      1/2	= 	0.5
 *      1/3	= 	0.(3)
 *      1/4	= 	0.25
 *      1/5	= 	0.2
 *      1/6	= 	0.1(6)
 *      1/7	= 	0.(142857)
 *      1/8	= 	0.125
 *      1/9	= 	0.(1)
 *      1/10	= 	0.1
 *
 * Where 0.1(6) means 0.166666..., and has a 1-digit recurring
 * cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
 *
 * Find the value of d < 1000 for which 1/d contains the longest
 * recurring cycle in its decimal fraction part. */

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<uint8_t> getFractional(const unsigned &);

unsigned getRecDigits(const std::vector<uint8_t> &);

typedef std::vector<uint8_t>::const_iterator vec_it;
bool checkCycle(vec_it, vec_it);

int main() {
    std::vector<uint8_t> fracDigits;
    unsigned recurringDigits = 0;
    unsigned maxDigits = 0;
    unsigned result = 0;

    for( auto i=999u; i>1; --i ) {
        // get fractional digits from long division
        fracDigits = getFractional(i);

        // count recurring digits, if applicable
        if( fracDigits.size() == 3*(i-1) )
            recurringDigits = getRecDigits(fracDigits);
        else continue; // fracDigits is non-recurring

        // record max, if available
        if( recurringDigits > maxDigits ) {
            maxDigits = recurringDigits;
            result = i;
        }
        else if( i < maxDigits )
            break;  // smaller i will only give smaller digits
    }

    std::cout << "result: " << result << std::endl;
    std::cout << "digits: " << maxDigits << std::endl;
}

inline
bool checkCycle(vec_it firstCycle_it, vec_it secondCycle_it) {
    auto limit_it = secondCycle_it;
    do
        if( *firstCycle_it++ != *secondCycle_it++ ) return false;
    while( firstCycle_it < limit_it );

    return true;
}


unsigned getRecDigits(const std::vector<uint8_t> &frac) {
    // look for cycles in reverse, due to leading zeroes,
    // for example, 1/300 = 0.0033...; easier to start at end
    auto maxDigits = frac.size()/3u;
    auto digits = 1u;
    auto end_it = frac.end();
    bool foundCycle = false;
    do {
        foundCycle = checkCycle( end_it-2*digits, end_it-digits );
        if( foundCycle ) return digits;
    } while( ++digits <= maxDigits );
    return 0;
}

std::vector<uint8_t> getFractional(const unsigned &divisor) {
    // perform long division of 1 / divisor
    std::vector<uint8_t> fractional;

    // up to (divisor-1) remainders can exist
    // multiple of 3 to guarantee 2 cycles
    auto limit = 3u * (divisor-1);

    auto dividend = 1u;
    for( auto i=0u; i<limit; ++i ) {
        dividend *= 10;
        fractional.push_back( static_cast<uint8_t>( dividend / divisor ) );
        dividend -= divisor*fractional.back();  // this is the remainder
        if( dividend==0 ) break;    // non-recurring decimals
    }
    return fractional;
}
