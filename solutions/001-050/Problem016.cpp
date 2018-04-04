/* Power digit sum
 * 2^15 = 32768 and the sum of its digits is
 * 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2^1000? */

#include <iostream>
#include <iterator>

int main() {
    auto digit=0u, carry=0u;
    std::string num("1");
    for( auto i=0u; i<1000; ++i ) {
        carry = 0;
        for (auto j = 0u; j < num.size(); ++j) {
            digit = (num[ j ] - '0') * 2u + carry;
            carry = digit > 9 ? 1 : 0;
            digit -= carry * 10;
            num[ j ] = static_cast<char>( '0' + digit );
        }
        if( carry>0 ) num.push_back(static_cast<char>( '0' + carry ));
    }

    long long result=0;
    for( auto i=0u; i<num.size(); ++i ) result += num[i]-'0';

    std::cout << "result: " << result <<std::endl;
}