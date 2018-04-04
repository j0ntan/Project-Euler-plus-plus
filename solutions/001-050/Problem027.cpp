/* Quadratic primes
 * Euler discovered the remarkable quadratic formula:
 *
 *                    n^2 + n + 41
 *
 * It turns out that the formula will produce 40 primes
 * for the consecutive integer values 0 ≤ n ≤ 39. However,
 * when n = 40, 402+40+41 = 40(40+1)+41 is divisible by 41,
 * and certainly when n = 41, 412+41+41 is clearly divisible
 * by 41.
 *
 * The incredible formula n^2−79n+1601 was discovered, which
 * produces 80 primes for the consecutive values 0 ≤ n ≤ 79.
 * The product of the coefficients, −79 and 1601, is −126479.
 *
 * Considering quadratics of the form:
 *
 *      n^2 + an + b, where |a|<1000 and |b|≤1000
 *
 *      where |n| is the modulus/absolute value of n
 *      e.g. |11|=11 and |−4|=4
 *
 * Find the product of the coefficients, a and b, for the
 * quadratic expression that produces the maximum number of
 * primes for consecutive values of n, starting with n = 0. */

#include <iostream>
#include <cmath>

bool isPrime(unsigned candidate);

int main() {
    auto maxConsecPrimes = 0u;
    auto maxA = 0;
    auto maxB = 0;
    for( auto a=-1000; a<1000; ++a )
        for( auto b=2; b<=1000; ++b ) {     // see footnote 1
            auto consecutivePrime = true;   // assume this
            auto n=0u;
            auto candidate = 0;
            while( consecutivePrime ) {
                candidate = n*n + a*n + b;
                if( candidate >= 2 ) {
                    consecutivePrime = isPrime( candidate*1u );
                    ++n;
                }
                else
                    consecutivePrime = false;
            }
            if( n > maxConsecPrimes ) {
                maxConsecPrimes = n;
                maxA = a;
                maxB = b;
            }
        }

    std::cout << "result: "
              << "a=" << maxA << ", "
              << "b=" << maxB << ", "
              << "a*b=" << maxA * maxB
              << std::endl;
}

bool isPrime(unsigned n) {
    if( n==1 ) return false;
    else if( n<4 ) return true;
    else if( n%2 == 0 ) return false;
    else if( n<9 ) return true;
    else if( n%3 == 0 ) return false;
    else {
        auto r = static_cast<long long>( std::floor( std::sqrt( static_cast<float>(n) ) ) );
        unsigned f = 5;
        while( f<=r ) {
            if( n%f == 0 ) return false;
            if( n%(f+2) == 0 ) return false;
            f += 6;
        }
        return true;
    }
}

/* footnote 1:
 *      Since we must begin with n=0, our first test in every
 *      case is just b. Therefore, it makes sense to avoid
 *      negative numbers for b, or just start at the first
 *      prime number, i.e. 2. */
