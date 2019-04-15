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
    std::cout << "Could not find the smallest prime below 65003 with an eight "
                 "prime value family.\n";
  else
    std::cout << "Smallest prime: " << ans << std::endl;
}

bool hasMinimumPrimes(const std::vector<unsigned int> &possiblePrimes) {
  const unsigned int MINIMUM_PRIMES = 7;
  unsigned int num_of_composite = 0;
  for (unsigned int i = 0;
       i < possiblePrimes.size() && num_of_composite <= 10 - MINIMUM_PRIMES;
       ++i) {
    if (!projEuler::isPrime(possiblePrimes[i]))
      ++num_of_composite;
  }
  return num_of_composite <= 10 - MINIMUM_PRIMES;
}

std::vector<unsigned int>
generatePossiblePrimes(unsigned int i, unsigned int j, unsigned int filler,
                       unsigned int additional_digits) {
  std::vector<unsigned int> retval;
  retval.reserve(10);

  // observe which digits need to be filled in
  const unsigned int LEADING_DIGIT_VACANCIES = i;
  const unsigned int IN_BETWEEN_DIGIT_VACANCIES = j - i - 1;
  const unsigned int TRAILING_DIGIT_VACANCIES = additional_digits;

  const unsigned int TOTAL_DIGITS = (j + 1) + TRAILING_DIGIT_VACANCIES;
  const unsigned int TOTAL_VACANCIES = TOTAL_DIGITS - 2;

  // construct appropriate filler string with leading zeros (i.e. "001" vs "1")
  std::string filler_str = std::to_string(filler);
  if (TOTAL_VACANCIES)
    filler_str =
        std::string(TOTAL_VACANCIES - filler_str.size(), '0') + filler_str;

  // form base str, e.g. 56**3 has filler = 563
  std::string base(TOTAL_DIGITS, '*');

  // keep track of which digits are used to fill in vacancies
  unsigned int filler_idx = 0;

  // fill in digits, conditionally
  if (LEADING_DIGIT_VACANCIES)
    for (unsigned int k = 0; k < LEADING_DIGIT_VACANCIES; ++k)
      base[k] = filler_str[filler_idx++];
  if (IN_BETWEEN_DIGIT_VACANCIES)
    for (unsigned int k = 0; k < IN_BETWEEN_DIGIT_VACANCIES; ++k)
      base[(i + 1) + k] = filler_str[filler_idx++];
  if (TRAILING_DIGIT_VACANCIES)
    for (unsigned int k = 0; k < TRAILING_DIGIT_VACANCIES; ++k)
      base[(j + 1) + k] = filler_str[filler_idx++];

  // add replacement digits & record result
  for (int k = 0; k < 10; ++k) {
    base[i] = '0' + k;
    base[j] = '0' + k;
    retval.push_back(std::stoi(base));
  }

  return retval;
}

unsigned int pow10(unsigned int n) {
  if (n == 0)
    return 1;
  else
    return 10 * pow10(--n);
}

int smallest8PrimeFamilyPrime() {
  const unsigned int MAX_DIGITS = 5;

  for (unsigned int i = 0; i < MAX_DIGITS - 1; ++i)
    for (unsigned int j = i + 1; j < MAX_DIGITS; ++j) {
      for (unsigned int additional_digits = 0;
           additional_digits < MAX_DIGITS - j; ++additional_digits) {
        const unsigned int FILLER_LIMIT = pow10(j - 1 + additional_digits);
        for (unsigned int filler_num = 0; filler_num < FILLER_LIMIT;
             ++filler_num) {
          auto possible_primes =
              generatePossiblePrimes(i, j, filler_num, additional_digits);
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
 * */
