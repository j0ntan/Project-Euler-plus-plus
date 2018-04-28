/* Powerful digit counts
 * The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit
 * number, 134217728=8^9, is a ninth power.
 *
 * How many n-digit positive integers exist which are also an nth power? */

#include "../../utils/StrNum/StrNum.h"
#include <iostream>

unsigned compareDigitCount(unsigned base);

int main() {
  unsigned count = 0;

  for (unsigned base = 1; base <= 9; ++base)
    count += compareDigitCount(base);

  std::cout << "Counted " << count
            << " integers with matching exponent & digit-count.";
}

unsigned compareDigitCount(unsigned base) {
  unsigned matches = 0;
  StrNum base_str(base);
  auto multiple_str = base_str;

  unsigned exponent = 1;
  while (multiple_str.size() == exponent++) {
    ++matches;
    multiple_str = multiple_str * base_str;
  }

  return matches;
}

/* First thoughts
 * 1. For the first few numbers, the exponent will increase faster than the
 * digit-count. We must still consider these numbers, starting from 1, because
 * they will at least have a match for an exponent/digit-count of one.
 * 2. As an upper limit to the base, we can examine a base of 10. We can observe
 * that the digit-count will always be one larger than the exponent. This
 * behavior carries onto bases larger than 10, so that we must set an upper
 * limit of 9 for the base.
 * 3. In order to avoid any problems with overflow, we use a big integer class
 * to perform calculations. */
