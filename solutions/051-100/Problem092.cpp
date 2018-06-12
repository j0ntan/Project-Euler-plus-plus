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

#include "../../utils/utils.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// function prototypes
const std::vector<unsigned> createNumberChain(unsigned first_link);

const unsigned LAST_STARTING_NUMBER = 10'000'000;
enum class ChainEnding { unknown, one, eighty_nine };

int main() {
  std::vector<ChainEnding> endings(LAST_STARTING_NUMBER, ChainEnding::unknown);
  endings[1] = ChainEnding::one;
  endings[89] = ChainEnding::eighty_nine;

  for (unsigned starting_num = 1; starting_num < LAST_STARTING_NUMBER;
       ++starting_num)
    if (endings[starting_num] == ChainEnding::unknown) {
      auto chain = createNumberChain(starting_num);
      if (chain.back() == 89u)
        endings[starting_num] = ChainEnding::eighty_nine;
      else
        endings[starting_num] = ChainEnding::one;
    }

  std::cout << "Total of starting numbers that arrive at 89 is "
            << std::count(endings.cbegin(), endings.cend(),
                          ChainEnding::eighty_nine);
}

bool reachedEndOfChain(unsigned chain_link) {
  static const unsigned one{1};
  static const unsigned eighty_nine{89};
  return chain_link == one || chain_link == eighty_nine;
}

const std::vector<unsigned> eachDigitSquared(unsigned num) {
  std::vector<unsigned> squared_digits(projEuler::getDigits(num));
  std::transform(squared_digits.begin(), squared_digits.end(),
                 squared_digits.begin(),
                 [](unsigned num) { return num * num; });
  return squared_digits;
}

const unsigned sumOfSquaredDigits(unsigned num) {
  const auto squared_digits = eachDigitSquared(num);
  return std::accumulate(squared_digits.begin(), squared_digits.end(), 0u);
}

const std::vector<unsigned> createNumberChain(unsigned first_link) {
  std::vector<unsigned> chain{first_link};
  while (not reachedEndOfChain(chain.back()))
    chain.emplace_back(sumOfSquaredDigits(chain.back()));
  return chain;
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
 * numbers.
 * 4. Sticking with regular integers rather than string-based ones will be
 * easier because the number formed by the permutations of those digits will be
 * used as an index. Thus, we'll use a utility function instead. */
