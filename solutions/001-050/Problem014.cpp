/* Longest Collatz sequence
 * The following iterative sequence is defined for the set of
 * positive integers:
 *
 *      n → n/2 (n is even)
 *      n → 3n + 1 (n is odd)
 *
 * Using the rule above and starting with 13, we generate the
 * following sequence:
 *
 *                     13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 *
 * It can be seen that this sequence (starting at 13 and finishing
 * at 1) contains 10 terms. Although it has not been proved yet (Collatz
 * Problem), it is thought that all starting numbers finish at 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 * NOTE: Once the chain starts the terms are allowed to go above one
 * million. */

#include <iostream>
#include <cmath>

void simpleSolution();

int main() {
    simpleSolution();
}

unsigned collatzTerms(unsigned n) {
    unsigned count=1; // last term included

    while( n>1 ) {
        if( n%2 == 0 ) {
            /*
            auto numLog = std::log2(n);
            if( numLog == std::floor(numLog) ) {
                count += static_cast<unsigned>(numLog);
                break;
            }
            else
                // The above is slower than simply dividing by 2
                */
                n /= 2;
        }
        else n = 3*n + 1;
        ++count;
    }

    return count;
}
void simpleSolution() {
    unsigned maxTerms=0;
    unsigned terms=0;
    unsigned collatzSeed=0;

    for( auto i=1u; i<1000000; ++i ) {
        terms = collatzTerms(i);
        if( terms > maxTerms ) {
            collatzSeed = i;
            maxTerms = terms;
        }
    }

    std::cout << "result: " << collatzSeed << std::endl;
}
