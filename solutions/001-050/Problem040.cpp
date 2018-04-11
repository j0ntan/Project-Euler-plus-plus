/* Champernowne's constant
 *
 * An irrational decimal fraction is created by concatenating the positive
 * integers:
 *
 *                 0.123456789101112131415161718192021...
 *
 * It can be seen that the 12th digit of the fractional part is 1.
 *
 * If d_n represents the n^th digit of the fractional part, find the value of
 * the following expression.
 *
 *       d_1 × d_10 × d_100 × d_1000 × d_10000 × d_100000 × d_1000000 */

#include <iostream>
#include <string>

// function prototypes
unsigned countDigits(unsigned num);
unsigned numAt(unsigned num, unsigned pos);

int main() {
  unsigned champernowne_constant = 1;
  const unsigned bounding_digit = 1'000'000;
  unsigned consecutive_num = 0;
  unsigned digits_count = 0;
  unsigned position_of_interest = 1;

  while (digits_count < bounding_digit) {
    unsigned current_num_of_digits = countDigits(++consecutive_num);

    if (digits_count < position_of_interest and
        (digits_count + current_num_of_digits) >= position_of_interest) {
      champernowne_constant *=
          numAt(consecutive_num, position_of_interest - digits_count);
      position_of_interest *= 10;
    }

    digits_count += current_num_of_digits;
  }

  std::cout << "The Champernowne constant is " << champernowne_constant;
}

unsigned countDigits(unsigned num) {
  unsigned digits = 0;
  while (num > 0) {
    num /= 10;
    ++digits;
  }
  return digits;
}

unsigned numAt(unsigned num, unsigned pos) {
  // first digit has position 1
  std::string str = std::to_string(num);
  return static_cast<unsigned>(std::stoi(str.substr(pos - 1, 1)));
}

/* Thought process
 * 1. One possible, but not best, solution is to use a string-based integer and
 * append consecutive numbers until the size of the number reaches 1,000,002
 * (one-million decimal digits + leading zero & decimal point).
 * 2. A better solution is to increase a counter of consecutive integers that
 * would be added to the fractional part. Another counter would keep track of
 * how many digits are being added to the fractional part. The needed digits can
 * be read and multiplied into the result. */
