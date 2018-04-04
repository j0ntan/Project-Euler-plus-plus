/* Summation of primes
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million. */

#include<iostream>
#include<cmath>

long long nextPrime(long long);
void simpleSolution();
bool isPrime(long long);
void betterSolution();

int main() {
    //simpleSolution();
    betterSolution();
}

long long nextPrime(long long n) {
    int factors=0;
    long long prime = n;
    while( factors != 2 ) {
        prime += 2;
        factors = 0;
        for( long long divisor=1; divisor <= prime; divisor += 2 )
            if( prime%divisor == 0 ) ++factors;
            else if( factors>2 ) break;
    }
    return prime;
}
void simpleSolution() {
    // The brute force approach, takes quite a while

    long long sum=2+3, prime=3;
    int i=2;
    do {
        prime = nextPrime(prime);
        sum += prime;
        ++i;
        if( i%10000 == 0 ) std::cout << prime << std::endl;
    } while( prime<2000000 );

    sum -= prime;
    std::cout << "\nresult: " << sum << std::endl;
}
bool isPrime(long long n) {
    if( n==1 ) return false;
    else if( n<4 ) return true;
    else if( n%2 == 0 ) return false;
    else if( n<9 ) return true;
    else if( n%3 == 0 ) return false;
    else {
        auto r = static_cast<long long>( std::floor( std::sqrt( static_cast<float>(n) ) ) );
        long long f = 5;
        while( f<=r ) {
            if( n%f == 0 ) return false;
            if( n%(f+2) == 0 ) return false;
            f += 6;
        }
        return true;
    }
}
void betterSolution() {
    // Uses the optimized isPrime() function from ID7
    long long sum=2+3, prime=3;
    do {
        prime += 2;
        if( isPrime(prime) )sum += prime;
    } while( prime<2000000 );

    std::cout << "\nresult: " << sum << std::endl;
}
