/* Double-base palindromes
 * The decimal number, 585 = 10010010012 (binary), is
 * palindromic in both bases.
 *
 * Find the sum of all numbers, less than one million, which
 * are palindromic in base 10 and base 2.
 *
 * (Please note that the palindromic number, in either base,
 * may not include leading zeros.) */

#include <iostream>
#include <vector>
#include <numeric>
#include "../../utils/utils.h"

std::string convDec2Str(unsigned num);

std::string conv2BinStr(unsigned num);

int main() {
    const auto limit = static_cast<unsigned>(1e6);

    std::vector<unsigned> doublePalindromes;

    for( auto i=0u; i<limit; ++i ) {
        using namespace projEuler;
        auto decStr = convDec2Str(i);
        auto binStr = conv2BinStr(i);
        if( isPalindrome(decStr) && isPalindrome(binStr) )
            doublePalindromes.push_back(i);
    }

    auto &p = doublePalindromes; // alias for brevity
    std::cout << "result: "
              << std::accumulate(p.begin(),p.end(),0u)
              << std::endl;
}

std::string conv2BinStr(unsigned num) {
    std::string binStr;
    while( num>0 ) {
        auto remain = num%2;
        if( remain==1 )
            binStr.push_back('1');
        else
            binStr.push_back('0');
        num /= 2;
    }
    return std::string( binStr.rbegin(),binStr.rend() );
}

std::string convDec2Str(unsigned num) {
    return std::to_string(num);
}