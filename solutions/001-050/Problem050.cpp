/* Consecutive prime sum
 * The prime 41, can be written as the sum of six consecutive
 * primes:
 *
 *                  41 = 2 + 3 + 5 + 7 + 11 + 13
 *
 * This is the longest sum of consecutive primes that adds to
 * a prime below one-hundred.
 *
 * The longest sum of consecutive primes below one-thousand that
 * adds to a prime, contains 21 terms, and is equal to 953.
 *
 * Which prime, below one-million, can be written as the sum of
 * the most consecutive primes? */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "../../utils/utils.h"

std::vector<unsigned> constructPartials(const std::vector<unsigned> &primes, unsigned offset, unsigned limit);

bool checkIfMax(unsigned maxSum, std::vector<unsigned> partials);

int main() {
    const auto limit = 1'000'000u;

    auto primes = projEuler::getPrimesList(2, limit-1);
    std::pair<unsigned,unsigned> primeAndSum {0u,0u};

    bool foundMaxConsecSum = false;
    do {
        static auto primesOffset = 0u;
        auto partials = constructPartials(primes, primesOffset, limit);

        foundMaxConsecSum = checkIfMax(primeAndSum.second, partials) or
                            primesOffset == primes.size()-2;

        if( !foundMaxConsecSum and std::any_of(
                partials.rbegin(), partials.rend() - primeAndSum.second
                , projEuler::isPrime) ) {
            auto primeLocation = std::find_if(
                    partials.rbegin(), partials.rend() - primeAndSum.second
                    , projEuler::isPrime );
            auto consecSum = static_cast<unsigned >(
                    partials.rend() - primeLocation );
            if( consecSum > primeAndSum.second )
                primeAndSum = {*primeLocation,consecSum};
        } // else nothing
        ++primesOffset;
    } while( !foundMaxConsecSum );

    std::cout << "result: " << primeAndSum.first << std::endl
              << "contains: " << primeAndSum.second
              << " terms " << std::endl;
}

bool checkIfMax(unsigned maxSum, std::vector<unsigned> partials) {
    return partials.size() < maxSum;
}

std::vector<unsigned>
constructPartials(const std::vector<unsigned> &primes
        , unsigned offset, unsigned limit) {
    std::vector<unsigned> partials;
    std::partial_sum( primes.begin()+offset, primes.end()
            , std::back_inserter(partials) );
    // NOTE: for a large limit, the partial sums will
    // overflow, but we can still use the values below
    // the limit value, at the start of the vector

    auto cutoffPoint = std::find_if( partials.begin(), partials.end()
            , std::bind2nd( std::greater_equal<unsigned>(), limit) );

    while( partials.end() != cutoffPoint )
        partials.pop_back();

    return partials;
}
