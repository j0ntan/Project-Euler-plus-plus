/* Square digit chains
 * A number chain is created by continuously adding the square of the digits in
 * a number to form a new number until it has been seen before.
 *
 * For example,
 *
 *        44 -> 32 -> 13 -> 10 -> 1 -> 1
 *        85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89
 *
 * Therefore any chain that arrives at 1 or 89 will become stuck in an endless
 * loop. What is most amazing is that EVERY starting number will eventually
 * arrive at 1 or 89.
 *
 * How many starting numbers below ten million will arrive at 89? */

#include "../../utils/StrNum/StrNum.h"
#include <iostream>
#include <numeric>
#include <vector>

// function prototypes
const StrNum sumOfSquaredDigits(const StrNum &num);
bool reachedEndOfChain(const StrNum &chain_link);

const unsigned LAST_STARTING_NUMBER = 10'000'000;

int main() {
  unsigned targets_hit = 0;

  for (unsigned starting_num = 1; starting_num < LAST_STARTING_NUMBER;
       ++starting_num) {
    StrNum chain_link{starting_num};
    while (not reachedEndOfChain(chain_link))
      chain_link = sumOfSquaredDigits(chain_link);
    if (chain_link == StrNum{89u})
      ++targets_hit;
  }

  std::cout << "Total of starting numbers that arrive at 89 is " << targets_hit;
}

bool reachedEndOfChain(const StrNum &chain_link) {
  static const StrNum one{1u};
  static const StrNum eighty_nine{89u};
  return chain_link == one || chain_link == eighty_nine;
}

const std::vector<StrNum> eachDigitSquared(const StrNum &num) {
  std::vector<StrNum> squared_digits(num.size(), StrNum(0u));
  for (unsigned i = 0; i < num.size(); ++i)
    squared_digits[i] = StrNum(num[i]) * StrNum(num[i]);
  return squared_digits;
}

const StrNum sumOfSquaredDigits(const StrNum &num) {
  const auto squared_digits = eachDigitSquared(num);
  return std::accumulate(squared_digits.begin(), squared_digits.end(),
                         StrNum{0u});
}

/* First thoughts
 * 1. This problem seems straight-forward, as in the simplest approach is using
 * brute-force computation.
 * 2. Using string-based integers will make working with individual digits
 * easier.
 * 3. This approach takes too long to finish and had to be terminated early. We
 * can observe that for a given number with more than one digit, the numbers
 * resulting from a permutation of those digits will have the same links in the
 * chain. Thus, the performance can be improved by skipping those permuted
 * numbers. */
