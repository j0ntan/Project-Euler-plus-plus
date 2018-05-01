/* Large non-Mersenne prime
 * The first known prime found to exceed one million digits was discovered in
 * 1999, and is a Mersenne prime of the form 2^69752593 - 1; it contains exactly
 * 2,098,960 digits. Subsequently other Mersenne primes, of the form 2^p - 1,
 * have been found which contain more digits.
 *
 * However, in 2004 there was found a massive non-Mersenne prime which contains
 * 2,357,207 digits: 28433 x 2^7830457 + 1.
 *
 * Find the last ten digits of this prime number.*/

#include <iostream>
#include "../../utils/StrNum/StrNum.h"

int main() {
  StrNum prime_num{2u};

  for(unsigned exp = 1; exp < 7830457; ++exp) {
    prime_num = prime_num * StrNum{2u};
    if (prime_num.size() > 10)
      prime_num = StrNum{prime_num.substr(prime_num.size() - 10)};
  }

  prime_num = prime_num * StrNum{28433u} + StrNum{1u};
  if (prime_num.size() > 10)
    prime_num = StrNum{prime_num.substr(prime_num.size() - 10)};

  std::cout << prime_num;
}

/* First thoughts
 * 1. Since we are only interested in the last ten digits, we can truncate part
 * of the number as it increases during the calculation.*/
