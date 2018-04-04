/* Largest prime factor
 * The prime factors of 13195 are 5, 7, 13, 29.
 *
 * What is the largest prime factor of the number 600851475143 ? */

#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>

bool isPrime(long long);
void simpleSolution();

// sample numbers for testing:
long long target = 600851475143;
//long long target = 51475143;
//long long target = 253; // 11*23
//long long target = 541*1013;
//long long target = 19836; // 2*2*3*3*19*29

int main() {
    simpleSolution();
}

bool isPrime(long long n) {
    if( n==1 ) return false;
    else if( n<4 ) return true;
    else if( n%2 == 0 ) return false;
    else if( n<9 ) return true;
    else if( n%3 == 0 ) return false;
    else {
        auto r = static_cast<long long>( std::floor( std::sqrt(n) ) );
        long long f = 5;
        while( f<=r ) {
            if( n%f == 0 ) return false;
            if( n%(f+2) == 0 ) return false;
            f += 6;
        }
        return true;
    }
}
void simpleSolution() {
    // Compose list of 1000 primes.
    std::vector<long long> primes;
    primes.push_back(2);
    for( int i=0; i<2000-1; ++i ) {
        long long num = primes[i]+1;
        while( !isPrime(num) ) ++num;
        primes.push_back(num);
    }

    // Iterate through prime numbers. Divide target by prime
    // factors, as many times as possible.
    long long max_prime=target;
    int i=0;
    while( i<primes.size() )
        if( target%primes[i] == 0 ) {
            max_prime = primes[i];
            target /= max_prime;
        }
        else ++i;

    std::cout << "max prime: " << primes[primes.size()-1] << std::endl;
    std::cout << "result: " << max_prime << std::endl;
}
