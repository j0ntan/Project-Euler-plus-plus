/* Combinatoric selections
 * There are exactly ten ways of selecting three from five, 12345:
 *             123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
 * In combinatorics, we use the notation, 5C3 = 10.
 * In general,
 * nCr = n!/(r!(n-r)!), where r<=n, n!=n*(n-1)*...*3*2*1, and 0!=1.
 * It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
 * How many, not necessarily distinct, values of nCr, for 1 <= n <= 100, are
 * greater than one-million? */

#include <iostream>

// function prototypes
const unsigned countBelowMinNthRow(unsigned row);

int main() {
  unsigned counter = 0;

  for (unsigned n = 23; n <= 100; ++n) {
    const unsigned counted_below_minimum = countBelowMinNthRow(n);
    const unsigned total_values = n + 1;
    const unsigned nth_row_unique_values =
        (total_values % 2 == 0) ? total_values / 2 : (total_values + 1) / 2;
    counter += nth_row_unique_values - counted_below_minimum;
  }

  std::cout << "Combinations greater than one-million equals " << counter;
}

const unsigned countBelowMinNthRow(unsigned row) {
  return 0;
}

/* First thoughts
 * 1. For this problem, we can use the properties of Pascal's triangle, and its
 * relation to the value of a combination, to make some simplifications.
 * 2. A value of n corresponds to the nth row of the triangle, with the top
 * being row 0. The nth row will also have (n + 1) numbers in that row.
 * 3. The triangle is symmetrical and, for a given row, the numbers increase
 * from one until we reach the middle number of that row and then decreases back
 * to one.
 * 4. Instead of calculating every possible combination, for n less than or
 * equal to one-hundred, to find numbers greater than one-million, we can
 * calculate & count the numbers less than one-million for an nth row. Thus, the
 * numbers greater than one-million is half the row count minus the calculated
 * count. This avoids having to calculate large combinations, e.g. 100C50, which
 * would overflow on all built-in types. This can be done for all possible n. */
