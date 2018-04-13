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

#include <algorithm>
#include <iostream>

class fraction {
public:
  fraction() = default;
  fraction(unsigned numer, unsigned denom)
      : numerator(numer), denominator(denom) {}
  fraction(unsigned numer, const fraction &f)
      : numerator(numer * f.denominator), denominator(f.numerator) {}

  fraction(const fraction &rhs) = default;
  fraction &operator=(const fraction &rhs) = default;

  const fraction operator+(const fraction &rhs) const {
    fraction f;
    if (this->denominator == rhs.denominator)
      f = fraction{(this->numerator + rhs.numerator), this->denominator};
    else {
      unsigned lcm = LCM(this->denominator, rhs.denominator);
      unsigned multiple1 = lcm / this->denominator,
               multiple2 = lcm / rhs.denominator;
      f = fraction{(multiple1 * this->numerator + multiple2 * rhs.numerator),
                   lcm};
    }
    return f;
  }

  const unsigned numer() const { return numerator; }
  const unsigned denom() const { return denominator; }

  friend std::ostream &operator<<(std::ostream &os, const fraction &f) {
    os << "{ " << f.numerator << " / " << f.denominator << " }";
    return os;
  }

private:
  unsigned GCD(unsigned a, unsigned b) const {
    if (b == 0)
      return a;
    else
      return GCD(b, a % b);
  }

  unsigned LCM(unsigned num1, unsigned num2) const {
    return num1 * num2 / GCD(num1, num2);
  }

  unsigned numerator = 0, denominator = 1;
};

// function prototypes
bool numerExceedsDenom(const fraction &f);

int main() {
  const unsigned EXPANSIONS = 1'000;
  unsigned larger_numer_digits = 0;

  fraction fractional_denominator{2, 1};
  for (unsigned iterations = 1; iterations < 25; ++iterations) {
    fractional_denominator =
        fraction{2, 1} + fraction{1, fractional_denominator};
    if (numerExceedsDenom(fraction{1, 1} + fraction{1, fractional_denominator}))
      ++larger_numer_digits;
  }

  // print 25th iteration
  std::cout << fraction{1, 1} + fraction{1, fractional_denominator}
            << std::endl;

  std::cout << "result = " << larger_numer_digits;
}

unsigned countDigits(unsigned n) {
  if (n > 0)
    return 1 + countDigits(n / 10);
  else
    return 0;
}

bool numerExceedsDenom(const fraction &f) {
  return countDigits(f.numer()) > countDigits(f.denom());
}

fraction continueTheFraction(unsigned iterations) {
  if (--iterations == 0)
    return fraction{2, 1};
  return fraction{2, 1} + fraction{1, continueTheFraction(iterations)};
}

/* Thought process
 * 1. This problem seems like a good fit for a recursive solution.
 * 2. First solution attempt fails, specifically at the 25th iteration. On this
 * iteration, we attempt to add 1 + {1,311,738,121 / 3,166,815,962} =
 * {4,478,554,083 / 3,166,815,962}. The numerator for this resulting fraction
 * overflows for 'unsigned int' type (2^32 - 1). Thus, we can next try using an
 * 'unsigned long long' type within the fraction class. In case this still
 * overflows, we can then try a string-based number representation. */
