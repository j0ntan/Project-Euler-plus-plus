/* Self powers
 * The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
 *
 * Find the last ten digits of the series,
 * 1^1 + 2^2 + 3^3 + ... + 1000^1000. */

#include <iostream>
#include <iterator>
#include "../../utils/StrNum/StrNum.h"

std::string calcSelfPwr(unsigned limit);

int main() {
    std::string result = calcSelfPwr(1000u);

    std::ostream_iterator<char> output(std::cout,nullptr);
    std::cout << "result: ";
    std::copy(result.end()-10,result.end(),output);
    std::cout << std::endl;
}

std::string calcSelfPwr(unsigned limit) {
    StrNum result;

    auto exponent = 1u;
    do {
        StrNum term(exponent);
        auto i = 1u;
        while( i++ < exponent ) {
            term = term * StrNum(exponent);
            // we only care about last 10 digits
            // **greatly reduces computation time**
            if( term.size() > 10 )
                term = std::string(term.end()-10
                        ,term.end());
        }
        result = result + term;
    } while( ++exponent <= limit );

    return result;
}