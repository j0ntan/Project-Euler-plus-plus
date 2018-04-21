/* Square root convergents
 * It is possible to show that the square root of two can be expressed as an
 * infinite continued fraction.
 *
 *       sqrt(2) = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...
 *
 * By expanding this for the first four iterations, we get:
 *
 * 1 + 1/2 = 3/2 = 1.5
 * 1 + 1/(2 + 1/2) = 7/5 = 1.4
 * 1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
 * 1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
 *
 * The next three expansions are 99/70, 239/169, and 577/408, but the eighth
 * expansion, 1393/985, is the first example where the number of digits in the
 * numerator exceeds the number of digits in the denominator.
 *
 * In the first one-thousand expansions, how many fractions contain a numerator
 * with more digits than denominator? */

#include "../../utils/StrNum/StrNum.h"
#include <algorithm>
#include <iostream>

class fraction {
public:
  fraction() = default;
  fraction(const unsigned &numer, const unsigned &denom)
      : numerator(StrNum{numer}), denominator(StrNum{denom}) {}
  fraction(const StrNum &numer, const StrNum &denom)
      : numerator(numer), denominator(denom) {}
  fraction(const unsigned &numer, const fraction &f)
      : numerator(StrNum{numer} * f.denominator), denominator(f.numerator) {}
  fraction(const StrNum &numer, const fraction &f)
      : numerator(numer * f.denominator), denominator(f.numerator) {}

  fraction(const fraction &rhs) = default;
  fraction &operator=(const fraction &rhs) = default;

  const fraction operator+(const fraction &rhs) const {
    return fraction{(this->numerator * rhs.denominator + rhs.numerator),
                    rhs.denominator};
  }

  const StrNum numer() const { return numerator; }
  const StrNum denom() const { return denominator; }

  friend std::ostream &operator<<(std::ostream &os, const fraction &f) {
    os << "{ " << f.numerator << " / " << f.denominator << " }";
    return os;
  }

private:
  /*
  StrNum GCD(const StrNum &a, const StrNum &b) const {
    if (b == StrNum{0})
      return a;
    else
      return GCD(b, a % b);
  }

  StrNum LCM(const StrNum &num1, const StrNum &num2) const {
    return num1 * num2 / GCD(num1, num2);
  }
  */

  StrNum numerator{0}, denominator{1};
};

// function prototypes
bool numerExceedsDenom(const fraction &f);

int main() {
  const unsigned EXPANSIONS = 1'000;
  unsigned larger_numer_digits = 0;

  fraction fractional_denominator{2, 1};
  for (unsigned iterations = 1; iterations < EXPANSIONS; ++iterations) {
    fractional_denominator =
        fraction{2, 1} + fraction{1, fractional_denominator};
    if (numerExceedsDenom(fraction{1, 1} + fraction{1, fractional_denominator}))
      ++larger_numer_digits;
  }

  std::cout << "result = " << larger_numer_digits;
}

/*
StrNum countDigits(const StrNum &n) {
  if (StrNum{0} < n)
    return StrNum{1} + countDigits(n / StrNum{10});
  else
    return StrNum{0};
}
*/

inline bool numerExceedsDenom(const fraction &f) {
  return f.numer().size() > f.denom().size();
}

/*
fraction continueTheFraction(unsigned iterations) {
  if (--iterations == 0)
    return fraction{2, 1};
  return fraction{2, 1} + fraction{1, continueTheFraction(iterations)};
}
*/

/* Thought process
 * 1. This problem seems like a good fit for a recursive solution.
 * 2. First solution attempt fails, specifically at the 25th iteration. On this
 * iteration, we attempt to add 1 + {1,311,738,121 / 3,166,815,962} =
 * {4,478,554,083 / 3,166,815,962}. The numerator for this resulting fraction
 * overflows for 'unsigned int' type (2^32 - 1). Thus, we can next try using an
 * 'unsigned long long' type within the fraction class. In case this still
 * overflows, we can then try a string-based number representation.
 * 3. After changing the fraction underlying type to 'unsigned long long', there
 * is still some overflow on the 51st iteration.
 * 4. The 'StrNum' implementation produces good results and does not have the
 * overflow problem on the 51st iteration like the previous implementation. Some
 * improvements can be made on several observations. Every occurrence of the sum
 * of two fractions includes one fraction that has a denominator of one. This
 * means that the least common multiple is simply the larger denominator. There
 * is no need to recursively look for greatest common divisor (GCD), thus we can
 * save on these function calls. Another improvement comes from the fact that
 * the numbers are string-based, so that the number of digits is simply the size
 * of the string. Again, there is no need to recursively call the function that
 * calculates the number of digits in a given number. */
