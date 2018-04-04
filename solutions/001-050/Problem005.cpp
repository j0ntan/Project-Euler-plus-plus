/* Smallest Multiple
 * 2520 is the smallest number that can be divided by each of the numbers from
 * 1 to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the
 * numbers from 1 to 20? */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void primitiveSolution();
void betterSolution();
void evenBetterSolution();

int main() {
    betterSolution();
    primitiveSolution();
    evenBetterSolution();
}

void primitiveSolution() {
    int multiple = 0, factor_count = 0;

    while( factor_count != 20 ) {
        ++multiple;
        factor_count = 0;
        for( int i=1; i<=20 ; ++i )
            if( multiple%i == 0 ) ++factor_count;
            else break;
    }
    std::cout << "result: " << multiple << std::endl;
}
void betterSolution() {
    // Calculate prime factors <= 20
    std::vector<int> factors_of_nums(20, 0);
    for( int i=0; i<20; ++i )
        for( int j=0; j<i+1; ++j )
            if( (i+1)%(j+1) == 0) ++factors_of_nums[i];
    std::vector<int> primes_list;
    for( int i=0; i<20; ++i )
        if( factors_of_nums[i]==2 ) primes_list.push_back(i+1);
    factors_of_nums.clear(); // clean-up

    // Find prime factors of each num in 1-20
    std::vector<std::vector<int>> factorization_list(20);
    for( int i=0,num = i+1; i<20; ++i ) {
        num = i+1;
        std::vector<int> factorization;
        for (int j=0; j<primes_list.size(); ++j) {
            num = i+1;
            while ( (num%primes_list[j]) == 0 ) {
                num /= primes_list[j];
                factorization.push_back(primes_list[j]);
            }
        }
        factorization_list[i].assign( factorization.begin(),
                                      factorization.end() );
    }

    // Find max uses of each prime in factorizations
    std::vector<int> max_uses(primes_list.size(), 0);
    for( int i=0; i<primes_list.size(); ++i ) {
        for( int j=i; j<20; ++j ) {
            int count = std::count( factorization_list[j].begin(),
                    factorization_list[j].end(), primes_list[i]);
            if( count > max_uses[i] ) max_uses[i] = count;
        }
    }

    // Solution is product of each (prime ^ max uses)
    int result = 1;
    for( int i=0; i<max_uses.size(); ++i )
        for( int j=0; j<max_uses[i]; ++j )
            result *= primes_list[i];

    std::cout << "result: " << result << std::endl;
}
void evenBetterSolution() {
    // Based on solution in overview
    int a[9] = {};                      // stores exponent for ea. prime
    int p[9] = {2,3,5,7,11,13,17,19,23};   // list of primes
    int k = 20;
    int N = 1;
    int i = 0;
    bool check = true;
    int limit = static_cast<int>( floor( sqrt(20) ) );

    do {
        a[i] = 1;
        if( check )
            if( p[i] <= limit )
                a[i] = static_cast<int>( floor( log(k)/log(p[i]) ) );
            else check = false;

        // floor() prevents cast error, particularly p[i]=13
        N = N * static_cast<int>( floor( pow(p[i], a[i]) ) );
    } while( p[++i] <= k );

    std::cout << "result: " << N << std::endl;
}
