/* Spiral primes
 * Starting with 1 and spiralling anticlockwise in the following way, a square
 * spiral with side length 7 is formed.
 *
 *                        37 36 35 34 33 32 31
 *                        38 17 16 15 14 13 30
 *                        39 18  5  4  3 12 29
 *                        40 19  6  1  2 11 28
 *                        41 20  7  8  9 10 27
 *                        42 21 22 23 24 25 26
 *                        43 44 45 46 47 48 49
 *
 * It is interesting to note that the odd squares lie along the bottom right
 * diagonal, but what is more interesting is that 8 out of the 13 numbers lying
 * along both diagonals are prime; that is, a ratio of 8/13 or approx. 62%.
 *
 * If one complete new layer is wrapped around the spiral above, a square spiral
 * with side length 9 will be formed. If this process is continued, what is the
 * side length of the square spiral for which the ratio of primes along both
 * diagonals first falls below 10%? */

#include "../../utils/utils.h"
#include <iomanip>
#include <iostream>

int main() {
  unsigned target_side_length = 0;
  const float RATIO_LIMIT = 10.0; // as percentage

  bool found_target_ratio = false;
  unsigned corner_hops = 2, spiral_num = 1, diagonal_size = 1, primes_found = 0;
  while (not found_target_ratio) {
    for (unsigned corner_traversed = 0; corner_traversed < 4;
         corner_traversed++, diagonal_size++) {
      spiral_num += corner_hops;
      if (projEuler::isPrime(spiral_num))
        primes_found++;
    }

    float current_ratio = 100 * static_cast<float>(primes_found) /
                          static_cast<float>(diagonal_size);

    found_target_ratio = current_ratio < RATIO_LIMIT;

    if (found_target_ratio) {
      target_side_length = corner_hops + 1;
      std::cout << spiral_num ;
      std::cout << "\ndiagonal size = " << diagonal_size
                << "\nprimes found = " << primes_found
                << "\ncurrent ratio = " << std::fixed << std::setprecision(2)
                << current_ratio << '%' << "\n\n";
    }

    corner_hops += 2;
  }

  std::cout << "Side length is " << target_side_length;
}

/* First thoughts
 * 1. For every individual layer, there is a fixed distance between the four
 * corners. As the we add the next layer, this distance is increased by two.
 * 2. As we add a new layer, the size of the diagonals increases by 4, for each
 * corner of the layer added. We can track the size of the diagonals, as well as
 * the number of primes that we add to the diagonals with counters as we add a
 * new layer. */
