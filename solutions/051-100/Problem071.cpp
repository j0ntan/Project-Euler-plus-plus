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

#include <cmath>
#include <iostream>

// function prototypes
const unsigned findNearestNumerator(unsigned denominator);
const double distanceFromTarget(unsigned numerator, unsigned denominator);

int main() {
  unsigned target_numerator = 0;
  double min_distance = 3.0 / 7.0;

  const unsigned DENOMINATOR_MAX = 1'000'000;
  for (unsigned current_denom = 3; current_denom <= DENOMINATOR_MAX;
       ++current_denom) {
    const auto corresponding_numer = findNearestNumerator(current_denom);
    const auto current_distance =
        distanceFromTarget(corresponding_numer, current_denom);
    if (current_distance < min_distance) {
      min_distance = current_distance;
      target_numerator = corresponding_numer;
    }
  }

  std::cout << "The numerator of the fraction to the left of 3/7 is "
            << target_numerator;
}

const unsigned findNearestNumerator(unsigned denominator) {
  auto numerator =
      static_cast<unsigned>(floor(3 * static_cast<double>(denominator) / 7));
  if (numerator % 3 == 0 and denominator % 7 == 0)
    --numerator;
  return numerator;
}

const double distanceFromTarget(unsigned numerator, unsigned denominator) {
  return 3.0 / 7.0 -
         static_cast<double>(numerator) / static_cast<double>(denominator);
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
 * form.
 * 4. Even after setting an upper bound for each denominator, there are too many
 * iterations to complete. The problem can be further simplified by only looking
 * at the fractions in the neighborhood of 3/7.
 * 5. Just as before, we want x = floor(3n/7) for a given denominator, n. If x/n
 * is a multiple of 3/7, we can take x-1 instead. Thus, we can look for the
 * minimum of 3/7 - x/n for n <= one-million. */
