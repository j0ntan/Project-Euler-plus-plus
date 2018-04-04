/* 10001st prime
 * By listing the first six prime numbers: 2, 3, 5, 7, 11,
 * and 13, we can see that the 6th prime is 13.
 *
 * What is the 10 001st prime number? */

#include <iostream>
#include <utility>
#include <cmath>

int getNextPrime(const int &);
void simpleSolution();
bool isPrime(int);
void betterSolution();

int main() {
    //simpleSolution();
    betterSolution();
}
void simpleSolution() {
    std::pair<int, int> primes = {3, 2};

    for( int i=0; i<9999; ++i ) {
        primes.second = getNextPrime(primes.first );
        std::swap( primes.first, primes.second );
    }

    std::cout << "result: " << primes.first << std::endl;
}
int getNextPrime(const int &current_prime) {
    auto nextPrime = current_prime;
    int factors = 0;

    while( factors != 2 ) {
        nextPrime += 2;
        factors = 0;
        for( int divisor = 1; divisor <= nextPrime; divisor += 2 )
            if( nextPrime%divisor == 0 ) ++factors;
    }
    return nextPrime;
}
bool isPrime(int n) {
    if( n==1 ) return false;
    else if( n<4 ) return true;
    else if( n%2 == 0 ) return false;
    else if( n<9 ) return true;
    else if( n%3 == 0 ) return false;
    else {
        int r = static_cast<int>( std::floor( std::sqrt(n) ) );
        int f = 5;
        while( f<=r ) {
            if( n%f == 0 ) return false;
            if( n%(f+2) == 0 ) return false;
            f += 6;
        }
        return true;
    }
}
void betterSolution() {
    // Based on solution in overview.
    int limit = 10001;
    int count = 1;      // we know that 2 is prime
    int candidate = 1;

    do {
        candidate += 2;
        if( isPrime(candidate) ) ++count;
    } while( count != limit );

    std::cout << "result: " << candidate << std::endl;
}
