/* Permuted multiples
 *
 * It can be seen that the number, 125874, and its double, 251748, contain
 * exactly the same digits, but in a different order.
 *
 * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
 * contain the same digits. */

#include "../../utils/utils.h"
#include <iostream>

struct DigitsCount {
  unsigned short zeroesCount = 0;
  unsigned short onesCount = 0;
  unsigned short twosCount = 0;
  unsigned short threesCount = 0;
  unsigned short foursCount = 0;
  unsigned short fivesCount = 0;
  unsigned short sixesCount = 0;
  unsigned short sevensCount = 0;
  unsigned short eightsCount = 0;
  unsigned short ninesCount = 0;
};

DigitsCount countAllDigits(unsigned wholeNumber);

bool operator==(const DigitsCount &lhs, const DigitsCount &rhs);

int main() {
  const unsigned STARTING_NUM = 100'000;

  unsigned x = STARTING_NUM;
  bool found_6_permutations = false;
  while (!found_6_permutations) {
    const DigitsCount digits_in_x = countAllDigits(x);

    bool found_a_permuted_multiple = true;
    for (auto multiplier = 2; multiplier <= 6 and found_a_permuted_multiple;
         multiplier++) {
      const unsigned multiple = multiplier * x;
      const DigitsCount digits_in_multiple = countAllDigits(multiple);
      found_a_permuted_multiple = (digits_in_x == digits_in_multiple);
    }

    found_6_permutations = found_a_permuted_multiple;
    if (found_6_permutations)
      std::cout << "x = " << x;

    x++;
  }
}

DigitsCount countAllDigits(unsigned wholeNumber) {
  DigitsCount result{};

  std::vector<unsigned short> allDigits =
      projEuler::getDigits<unsigned, unsigned short>(wholeNumber);

  for (auto digit : allDigits)
    switch (digit) {
    case 0:
      result.zeroesCount++;
      break;
    case 1:
      result.onesCount++;
      break;
    case 2:
      result.twosCount++;
      break;
    case 3:
      result.threesCount++;
      break;
    case 4:
      result.foursCount++;
      break;
    case 5:
      result.fivesCount++;
      break;
    case 6:
      result.sixesCount++;
      break;
    case 7:
      result.sevensCount++;
      break;
    case 8:
      result.eightsCount++;
      break;
    case 9:
      result.ninesCount++;
      break;
    default:
      break;
    }

  return result;
}

bool operator==(const DigitsCount &lhs, const DigitsCount &rhs) {
  return lhs.zeroesCount == rhs.zeroesCount && lhs.onesCount == rhs.onesCount &&
         lhs.twosCount == rhs.twosCount && lhs.threesCount == rhs.threesCount &&
         lhs.foursCount == rhs.foursCount && lhs.fivesCount == rhs.fivesCount &&
         lhs.sixesCount == rhs.sixesCount &&
         lhs.sevensCount == rhs.sevensCount &&
         lhs.eightsCount == rhs.eightsCount && lhs.ninesCount == rhs.ninesCount;
}

/* Thought process:
 * 1. Since we are multiplying by at most 6, we require 6 permutations, which in
 * turn requires at least 6 digits in the starting number. This places a lower
 * bound in the numbers we can try, which is 100,000, the lowest 6-digit number.
 * 2. There is no mention whether or not the digits can repeat between any of
 * the multiples. We will assume that repetition is allowed, thus we must check
 * that all digits and their repetitions for each multiple must match.
 * 3. Each multiple will be different than each other multiple. Thus, if all the
 * digits in 'x' occur in a multiple of that 'x', then it's guaranteed that the
 * multiple is a permutation of 'x'. This avoids creating a list of the
 * permutations of 'x' & looking up a multiple within the list, which can be
 * costly in time and memory. */
