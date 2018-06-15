/* Ordered fractions
 * Consider the fraction, n/d, where n and d are positive integers. If n<d and
 * HCF(n,d)=1, it is called a reduced proper fraction.
 *
 * If we list the set of reduced proper fractions for d <= 8 in ascending order
 * of size, we get:
 *
 * 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3,
 * 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 *
 * It can be seen that 2/5 is the fraction immediately to the left of 3/7.
 *
 * By listing the set of reduced proper fractions for d <= 1,000,000 in
 * ascending order of size, find the numerator of the fraction immediately to
 * the left of 3/7. */

#include <iostream>

// function prototypes

int main() {
  unsigned target_numerator = 0;
  std::cout << "The numerator of the fraction to the left of 3/7 is "
            << target_numerator;
}

/* First thoughts
 * 1. We cannot simply try all possible combinations, as there is a very large
 * number of combinations (1,000,000 choose 2). Instead, we can set an upper
 * bound, for any given denominator, that would result in a fraction greater
 * than 3/7, since we are only interested in the fraction immediately smaller
 * than this.
 * 2. To set an upper bound for a given denominator, d, we must find a
 * numerator, n, such that 3/7 >= x/n. Since n is always positive, this gives
 * x <= 3n/7, or x = floor(3n/7).
 * 3. Before we store a given fraction, it must be converted to its simplest
 * form. */
