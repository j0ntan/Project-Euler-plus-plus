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
#include <vector>

// function prototypes

int main() {
  unsigned counter = 0;
  std::vector<unsigned> current_row{1}, next_row;

  for (unsigned n = 0; n < 22; ++n) {
    // TODO: calculate row of Pascal's triangle
  }

  for (unsigned n = 23; n <= 100; ++n) {
    // TODO: calculate partial rows of Pascal's triangle & count values over
    // one-million
  }

  std::cout << "Combinations greater than one-million equals " << counter;
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
 * would overflow on all built-in types. This can be done for all possible n.
 * 5. For calculating the combination of n choose k, we cannot simply follow the
 * explicit formula, n!/(k! (n-k)!). Calculating n! will result in overflow for
 * large values of n, but we can simplify n!/(n-k)!. For this calculation some
 * terms cancel out, thus we only need to calculate n * (n-1) * ... * (n-k).
 * 6. There is still overflow after the previous simplification, thus requiring
 * another approach. An alternative method is to construct portions of the
 * Pascal's triangle for combination values less than one-million. This
 * completely avoids calculating large values than can overflow.
 * 7. The values for the triangle can be calculated the easy way, using the
 * values of the previous row. instead of using factorials.
 * 8. Due to symmetry, the calculated values repeat on the same row. Therefore,
 * for a given row, this calculated amount can be subtracted from the total
 * amount of values possible on that row, as we did before. */
