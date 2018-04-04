/* Non-abundant sums
 * A perfect number is a number for which the sum of its
 * proper divisors is exactly equal to the number. For example,
 * the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7
 * + 14 = 28, which means that 28 is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors
 * is less than n and it is called abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16,
 * the smallest number that can be written as the sum of two abundant
 * numbers is 24. By mathematical analysis, it can be shown that all
 * integers greater than 28123 can be written as the sum of two
 * abundant numbers. However, this upper limit cannot be reduced any
 * further by analysis even though it is known that the greatest number
 * that cannot be expressed as the sum of two abundant numbers is less
 * than this limit.
 *
 * Find the sum of all the positive integers which cannot be written
 * as the sum of two abundant numbers. */

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

bool isAbundant(unsigned num);

unsigned addFalse(unsigned total, bool abundSum);

int main() {
    const auto limit = 28123;

    // get list: abundant numbers i < 28123,
    std::vector<unsigned> abundantNums;
    for( auto i=12u; i < limit; ++i )
        if( isAbundant(i) )
            abundantNums.push_back(i);

    // get bool list: index of n + (n+m) is true, for
    // each sum of abundant num pair, false otherwise
    std::vector<bool> sumOfAbundants(limit,false);
    {
        auto start = abundantNums.begin();
        auto end = abundantNums.end();
        auto sum = 0u;
        for( auto term1_it=start; term1_it<end; ++term1_it )
            for( auto term2_it=term1_it; term2_it<end; ++term2_it ) {
                sum = *term1_it + *term2_it;
                if( sum <= limit )
                    sumOfAbundants[sum-1] = true;
                else break;
            }
    }

    // add indeces of non-sum terms, containing false, as the result
    std::cout << "result: "
              << std::accumulate( sumOfAbundants.begin(),
                                  sumOfAbundants.end(),
                                  0u,
                                  addFalse ) << std::endl;
}

unsigned addFalse(unsigned total, bool abundSum) {
    static auto count = 0u;
    ++count;
    return total + ( abundSum ? 0:count );
}


bool isAbundant(unsigned num) {
    // find divisors first, efficiently
    std::vector<unsigned> divisors;

    // first half of divisors
    auto limit = static_cast<unsigned>
            ( std::floor(std::sqrt(num))) ;
    for( auto i=1u; i<=limit; ++i )
        if( num%i == 0 )
            divisors.push_back(i);

    // other half
    auto size = divisors.size();
    for( auto i=1u; i<size-1; ++i )
        divisors.push_back( num/divisors[i] );

    // check that perfect squares don't add sqrt twice
    // and don't add num itself as factor
    --size;
    if( size>0 && divisors[size]*divisors[size] != num )
        divisors.push_back( num/divisors[size] );

    auto sum = std::accumulate( divisors.begin(),
                                divisors.end(),
                                0u );
    return sum > num;
}
