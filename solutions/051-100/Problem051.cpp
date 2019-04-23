/* Prime digit replacements
 *
 * By replacing the 1st digit of the 2-digit number *3, it turns out that six of
 * the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.
 *
 * By replacing the 3rd and 4th digits of 56**3 with the same digit, this
 * 5-digit number is the first example having seven primes among the ten
 * generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663,
 * 56773, and 56993. Consequently 56003, being the first member of this family,
 * is the smallest prime with this property.
 *
 * Find the smallest prime which, by replacing part of the number (not
 * necessarily adjacent digits) with the same digit, is part of an eight prime
 * value family. */

#include <iostream>
#include <string>
#include <vector>

#include <utils.h>

int smallest8PrimeFamilyPrime();

int main() {
  auto ans = smallest8PrimeFamilyPrime();
  if (ans == -1)
    std::cout << "Could not find the smallest prime with an eight prime value "
                 "family.\n";
  else
    std::cout << "Smallest prime: " << ans << std::endl;
}

bool hasMinimumPrimes(const std::vector<unsigned int> &possiblePrimes) {
  const unsigned int MINIMUM_PRIMES = 8;
  const unsigned int MAXIMUM_COMPOSITES =
      possiblePrimes.size() - MINIMUM_PRIMES;

  unsigned int num_of_composite = 0;
  for (unsigned int i = 0;
       i < possiblePrimes.size() && num_of_composite <= MAXIMUM_COMPOSITES;
       ++i) {
    if (!projEuler::isPrime(possiblePrimes[i]))
      ++num_of_composite;
  }

  return num_of_composite <= MAXIMUM_COMPOSITES;
}

unsigned int pow10(unsigned int n) {
  if (n == 0)
    return 1;
  else
    return 10 * pow10(--n);
}

std::vector<unsigned int> generatePossiblePrimes(unsigned int i, unsigned int j,
                                                 unsigned int base) {
  std::vector<unsigned int> retval;
  retval.reserve(10);

  auto base_digits = projEuler::getDigits(base);
  unsigned int summer =
      pow10(base_digits.size() - j - 1) + pow10(base_digits.size() - i - 1);

  base_digits[i] = base_digits[j] = 0;
  base = projEuler::combineDigits(base_digits);

  if (i != 0)
    retval.push_back(base);
  for (int k = 1; k < 10; ++k) {
    base += summer;
    retval.push_back(base);
  }

  return retval;
}

int smallest8PrimeFamilyPrime() {
  const unsigned int MIN_DIGITS = 5;
  const unsigned int MAX_DIGITS = 6;

  for (unsigned int n = MIN_DIGITS; n <= MAX_DIGITS; ++n) {
    const unsigned int Nth_DIGIT_LIMIT = pow10(n) - 1;
    for (unsigned int base_num = pow10(n - 1) + 1; base_num <= Nth_DIGIT_LIMIT;
         base_num += 2) {
      for (unsigned int i = 0; i < n - 2; ++i)
        for (unsigned int j = i + 1; j < n - 1; ++j) {
          auto possible_primes = generatePossiblePrimes(i, j, base_num);
          if (hasMinimumPrimes(possible_primes))
            return possible_primes.front();
        }
    }
  }

  return -1;
}

/* Thought process:
 * 1. It is not clear whether this smallest prime will be less-than or
 * greater-than 56003. Therefore, as a first attempt we can try a brute force
 * approach using values below 56003. A lower bound can be set as 10, the
 * smallest 2-digit number.
 * 2. Assuming we want to replace ONLY two numbers, we will choose two digits at
 * index i and j. Because we want to replace two numbers, i and j must differ.
 * For a chosen set of i and j, swapping their values will result in a duplicate
 * replacement. Thus, we always want i < j.
 * 3. Rather than iterating a number range, it is better to start with i and j,
 * followed by appending/filling in digits to form a set of numbers with the
 * chosen i and j. For example, let i and j be 0 and 1, respectively. The set of
 * two digit numbers (10-99) is covered by i and j. Next we add a third digit,
 * starting with appending 0. This covers the set of **0 numbers (i.e., 100,
 * 110, 120, ..., 990). We continue checking **1, **2, ..., **9. Then we add
 * another digit to get **00, followed by **01, **02, etc. We can stop (for now)
 * once we have reached 56**3, or when i = 2 and j = 3 and 5,6,3 fills in the
 * 5-digit number.
 * 4. At this point, the program can generate the desired values. There was one
 * misunderstanding that gave a false result. That is, it was a mistake to
 * consider the number 7, or 0007, to be in the same family as 1107 or 2207.
 * Numbers in the same family must have the same number of digits, not counting
 * any leading zeros.
 * 5. We are now able to calculate 56003 as the lowest prime in the 7 primes
 * family. The value for 8 primes family cannot be found yet, so we may need to
 * increase the max number of digits allowed.
 * 6. Increasing the maximum digits for computing possible primes is taking too
 * much time to execute. The code needs to be restructured and optimized to
 * improve execution time.
 * 7. Since 56003 is the smallest 7-prime-value-family prime number, it seems
 * like we can assume that we can ignore numbers with less than 5 digits. Thus,
 * when we generate an n-digit number we can begin with the smallest n-digit
 * number, i.e. 10^(n-1).
 * 8. We can exclude even numbers in our number generation to reduce the our
 * computations by roughly a half.
 * 9. Given an n-digit number, it does not make sense to replace the last digit
 * because it will result in creating several even numbers, which will not meet
 * the requirement of 8 primes.
 * */
