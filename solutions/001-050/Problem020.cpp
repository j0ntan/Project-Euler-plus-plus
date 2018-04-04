/* Factorial digit sum
 * n! means n × (n − 1) × ... × 3 × 2 × 1
 *
 * For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
 * and the sum of the digits in the number 10! is
 * 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 *
 * Find the sum of the digits in the number 100! */

#include <iostream>
#include <iterator>

int main() {
    std::string num("1");

    auto carry1=0u, carry2=0u;
    auto product=0u, digit=0u;
    for( auto i=1u; i<=100; ++i ) {
        carry1=carry2=0;
        for( auto j=0u; j<num.size(); ++j ) {
            product = i*( num[j]-'0' ) + 10*carry1 + carry2;
            carry1 = product/100;
            carry2 = ( product-100*carry1 ) / 10;
            digit = product - 100*carry1 - 10*carry2;
            num[j] = static_cast<char>( '0' + digit );
        }
        if( (10*carry1 + carry2) > 9 ) {
            num.append( std::to_string(carry2) );
            num.append( std::to_string(carry1) );
        }
        else if( carry2 > 0 )
            num.append(std::to_string(carry2));
    }

    std::ostream_iterator<char> output(std::cout,nullptr);
    std::cout << "num: ";
    std::copy(num.rbegin(),num.rend(),output);
    std::cout << std::endl << std::endl;

    auto result=0u;
    for( auto i=0u; i<num.size(); ++i ) result += num[i]-'0';
    std::cout << "result: " << result <<std::endl;
}