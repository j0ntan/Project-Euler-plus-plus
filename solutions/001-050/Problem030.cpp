/* Digit fifth powers
 * Surprisingly there are only three numbers that can be
 * written as the sum of fourth powers of their digits:
 *
 *      1634 = 1^4 + 6^4 + 3^4 + 4^4
 *      8208 = 8^4 + 2^4 + 0^4 + 8^4
 *      9474 = 9^4 + 4^4 + 7^4 + 4^4
 *
 * As 1 = 1^4 is not a sum it is not included.
 *
 * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
 *
 * Find the sum of all the numbers that can be written as
 * the sum of fifth powers of their digits. */

#include <iostream>
#include <vector>
#include <numeric>

unsigned sum5thPwrs(const std::vector<unsigned> &digits);

std::vector<unsigned> getDigits(unsigned num);

unsigned fifthPow(const unsigned &num);

int main() {
    std::vector<unsigned> validNums;

    // the lower limit must be a sum, i.e. 1^5 + 1^5 = 2
    // the upper limit given as 1e6, as approx. solution
    // of n*9^5 = 10^n
    {
        std::vector<unsigned> numDigits;
        const auto loBound = 11u;
        const auto upBound = 1000000u;
        auto sum = 0u;
        for( auto i=loBound; i<=upBound; ++i ) {
            numDigits = getDigits(i);
            sum = sum5thPwrs(numDigits);
            if( i == sum )
                validNums.push_back(i);
        }
    }

    std::cout << "result: "
              << std::accumulate( validNums.begin(),
                                  validNums.end(),
                                  0u )
              << std::endl;
}

std::vector<unsigned> getDigits(unsigned num) {
    std::vector<unsigned> digits;
    while( num > 0 ) {
        digits.push_back( num - (num/10)*10 );
        num /= 10;
    }

    // return in correct order
    return std::vector<unsigned>( digits.rbegin(),
                                  digits.rend() );
}

unsigned sum5thPwrs(const std::vector<unsigned> &digits) {
    auto sum = 0u;
    for( auto it=digits.begin(); it<digits.end(); ++it ) {
        sum += fifthPow(*it);
    }
    return sum;
}

inline
unsigned fifthPow(const unsigned &num) {
    return num*num*num*num*num;
}