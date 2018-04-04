/* Amicable numbers
 * Let d(n) be defined as the sum of proper divisors of n
 * (numbers less than n which divide evenly into n). If
 * d(a) = b and d(b) = a, where a ≠ b, then a and b are an
 * amicable pair and each of a and b are called amicable numbers.
 *
 * For example, the proper divisors of 220 are 1, 2, 4, 5,
 * 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284.
 * The proper divisors of 284 are 1, 2, 4, 71 and 142; so
 * d(284) = 220.
 *
 * Evaluate the sum of all the amicable numbers under 10000. */

#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <algorithm>

std::vector<unsigned> findDivisors(unsigned i);

int main() {
    auto num1 = 2u, num2 = num1;
    auto sum1 = 0u, sum2 = sum1;
    std::vector<unsigned> v_div1, v_div2;
    std::vector<unsigned> amicable;
    for( auto i=2u; i<10000; ++i ) {
        v_div1 = findDivisors(i);
        sum1 = std::accumulate(v_div1.begin(),v_div1.end(),0u);
        v_div2 = findDivisors(sum1);
        sum2 = std::accumulate(v_div2.begin(),v_div2.end(),0u);
        if( i==sum2 && sum1>i ) {
            amicable.push_back(i);
            amicable.push_back(sum1);
        }
    }

    auto result=0u;
    result = std::accumulate(amicable.begin(),amicable.end(),0u);
    std::cout << "result: " << result << std::endl;
}

std::vector<unsigned> findDivisors(unsigned num) {
    std::vector<unsigned> divisors;
    auto limit = static_cast<unsigned>( std::floor(std::sqrt(num))) ;
    for( auto i=1u; i<=limit; ++i )
        if( num%i == 0 )
            divisors.push_back(i);
    auto size = divisors.size();
    for( auto i=1u; i<size; ++i )
        divisors.push_back( num/divisors[i] );
    std::sort(divisors.begin(),divisors.end());
    return std::move(divisors);
}