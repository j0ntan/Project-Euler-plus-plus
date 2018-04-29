#include "StrNum.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <utility>

namespace {
const std::string &verifyNumericalString(const std::string &str) {
  const bool is_numerical =
      !str.empty() and std::find_if(str.begin(), str.end(), [](char c) {
                         return !std::isdigit(c);
                       }) == str.end();
  if (is_numerical)
    return str;
  else
    return std::move(std::string{"0"});
}

void exitOnNegativeDifference(const StrNum &lhs, const StrNum &rhs) {
  std::cerr << lhs << " - " << rhs << " results in a negative number"
            << std::endl;
  std::cerr << "Negative integers not yet supported." << std::endl;
  exit(1);
}

void removeTrailingZeros(std::string &str) {
  while (str.size() > 1 and str.back() == '0')
    str.pop_back();
}

void reverseString(std::string &str) {
  const unsigned num_swaps = str.size() / 2;
  for (unsigned i = 0; i < num_swaps; ++i)
    std::swap(str[i], str[str.size() - i - 1]);
}

void appendNextDigit(StrNum &partial_dividend, unsigned next_digit) {
  partial_dividend = partial_dividend * StrNum{10u} + StrNum{next_digit};
}

unsigned findNearestMultiple(const StrNum &divisor,
                             const StrNum &partial_dividend) {
  unsigned initial_guess = 0;
  if (divisor.size() == partial_dividend.size())
    initial_guess = partial_dividend.numAt(0) / divisor.numAt(0);
  else
    initial_guess =
        (10 * partial_dividend.numAt(0) + partial_dividend.numAt(1)) /
        divisor.numAt(0);

  while (partial_dividend < (divisor * StrNum{initial_guess}))
    --initial_guess;

  return initial_guess;
}

std::pair<StrNum, StrNum> longDivision(const StrNum &dividend,
                                       const StrNum &divisor) {
  std::string quotient, remainder;

  if (dividend.size() < divisor.size()) {
    quotient = "0";
    remainder = divisor; // no object slicing occurs
  } else {
    StrNum partial_dividend{0u};

    for (unsigned current_idx = 0; current_idx < dividend.size();
         ++current_idx) {
      appendNextDigit(partial_dividend, dividend.numAt(current_idx));

      if (divisor <= partial_dividend) {
        auto quotient_digit = findNearestMultiple(divisor, partial_dividend);
        quotient.append(std::to_string(quotient_digit));
        partial_dividend -= divisor * StrNum{quotient_digit};
      } else
        quotient.append("0");
    }

    remainder = partial_dividend;

    reverseString(quotient);       // move zeros from front to back
    removeTrailingZeros(quotient); // remove those zeros
    reverseString(quotient);       // correct the final order
  }

  return std::make_pair(StrNum{quotient}, StrNum{remainder});
}
} // namespace

StrNum::StrNum(const unsigned &numerical)
    : std::string(std::to_string(numerical)) {}

StrNum::StrNum(const std::string &str)
    : std::string(verifyNumericalString(str)) {}

StrNum::StrNum(const char &c) : std::string(1, c) {}

bool StrNum ::operator<(const StrNum &rhs) const {
  bool less_than = false;

  if (this->size() == rhs.size()) {
    for (unsigned i = 0; i < this->size(); ++i)
      if (this->numAt(i) != rhs.numAt(i)) {
        less_than = this->numAt(i) < rhs.numAt(i);
        break;
      }
  } else
    less_than = this->size() < rhs.size();

  return less_than;
}

bool StrNum::operator==(const StrNum &rhs) const {
  bool same_size = this->size() == rhs.size();

  bool same_elements = true;
  if (same_size)
    for (unsigned i = 0; i < this->size() and same_elements; ++i)
      same_elements = this->numAt(i) == rhs.numAt(i);

  return same_size and same_elements;
}

bool StrNum::operator<=(const StrNum &rhs) const {
  return *this == rhs or *this < rhs;
}

const StrNum StrNum::operator+(const StrNum &rhs) const {
  const StrNum *larger = this, *smaller = &rhs;
  if (this->size() < rhs.size())
    std::swap(larger, smaller);

  std::string sum;
  unsigned carry = 0;

  // add the first 'smaller->size()' digits in 'larger' and 'smaller'
  for (unsigned larger_idx = larger->size() - 1,
                smaller_idx = smaller->size() - 1, digits_added = 0;
       digits_added < smaller->size();
       --larger_idx, --smaller_idx, ++digits_added) {
    unsigned two_digit_sum = larger->numAt(larger_idx) +
                             smaller->numAt(smaller_idx) +
                             carry;            // any between 0-19
    carry = two_digit_sum / 10;                // either 0 or 1
    two_digit_sum -= 10 * carry;               // remove tens place
    sum.append(std::to_string(two_digit_sum)); // placed in reversed order
  }

  // add 'carry' to remaining digits in 'larger'
  const unsigned num_digits_remaining = larger->size() - smaller->size();
  for (unsigned larger_idx = num_digits_remaining - 1, digits_added = 0;
       digits_added < num_digits_remaining; --larger_idx, ++digits_added) {
    unsigned digit_plus_carry = larger->numAt(larger_idx) + carry;
    carry = digit_plus_carry / 10;
    digit_plus_carry -= 10 * carry;
    sum.append(std::to_string(digit_plus_carry));
  }

  // add any remaining carry
  if (carry == 1)
    sum.push_back('1');

  removeTrailingZeros(sum);

  // put into correct order by reversing digits
  reverseString(sum);

  return StrNum(sum);
}

const StrNum StrNum::operator-(const StrNum &rhs) const {
  std::string difference;

  // working with unsigned integers only for now
  if (*this < rhs) {
    exitOnNegativeDifference(*this, rhs);
  } else if (*this == rhs)
    difference = "0";
  else {
    bool borrowed_from = false;

    // get difference of first 'rhs.size()' digits
    for (unsigned larger_idx = this->size() - 1, smaller_idx = rhs.size() - 1,
                  digits_subtracted = 0;
         digits_subtracted < rhs.size();
         --larger_idx, --smaller_idx, ++digits_subtracted) {
      auto minuend = this->numAt(larger_idx),
           subtrahend = rhs.numAt(smaller_idx);

      if (borrowed_from and minuend == 0) {
        difference.append(std::to_string(9 - subtrahend));
        borrowed_from = true;
      } else {
        if (borrowed_from and minuend > 0)
          --minuend;

        borrowed_from = minuend < subtrahend;

        if (borrowed_from)
          difference.append(std::to_string((10 + minuend) - subtrahend));
        else
          difference.append(std::to_string(minuend - subtrahend));
      }
    }

    // borrow from remaining digits if needed
    const unsigned num_digits_remaining = this->size() - rhs.size();
    for (unsigned larger_idx = num_digits_remaining - 1,
                  digits_borrowed_from = 0;
         digits_borrowed_from < num_digits_remaining;
         --larger_idx, ++digits_borrowed_from) {
      auto remaining_digit = this->numAt(larger_idx);

      if (borrowed_from and remaining_digit == 0) {
        difference.append(std::to_string(9));
        borrowed_from = true;
      } else if (borrowed_from and remaining_digit > 0) {
        difference.append(std::to_string(--remaining_digit));
        borrowed_from = false;
      } else
        difference.append(std::to_string(remaining_digit));
    }
  }

  removeTrailingZeros(difference);

  reverseString(difference);

  return StrNum(difference);
}

const StrNum &StrNum::operator+=(const StrNum &rhs) {
  *this = *this + rhs;
  return *this;
}

const StrNum &StrNum::operator-=(const StrNum &rhs) {
  *this = *this - rhs;
  return *this;
}

const StrNum StrNum::operator*(const StrNum &rhs) const {
  const StrNum &m1 = *this; // multiplicand
  const StrNum &m2 = rhs;   // multiplier

  StrNum product{0u};

  for (unsigned m2_idx = m2.size() - 1, times_multiplied = 0;
       times_multiplied < m2.size(); --m2_idx, ++times_multiplied) {
    unsigned carry = 0;
    std::string sub_product(times_multiplied, '0');

    for (unsigned m1_idx = m1.size() - 1, single_digit_product = 0;
         single_digit_product < m1.size(); --m1_idx, ++single_digit_product) {
      unsigned two_digit_product =
          m1.numAt(m1_idx) * m2.numAt(m2_idx) + carry; // any between 0-90
      carry = two_digit_product / 10;                  // any between 0-9
      two_digit_product -= 10 * carry;                 // remove tens place
      sub_product.append(
          std::to_string(two_digit_product)); // placed in reverse order
    }

    if (carry > 0)
      sub_product.append(std::to_string(carry));

    reverseString(sub_product);

    product += StrNum(sub_product);
  }

  return product;
}

const StrNum StrNum::operator/(const StrNum &rhs) const {
  return longDivision(*this, rhs).first;
}

const StrNum StrNum::operator%(const StrNum &rhs) const {
  StrNum mod;
  if (*this < rhs)
    mod = *this;
  else
    mod = longDivision(*this, rhs).second;
  return mod;
}

const unsigned StrNum::numAt(unsigned idx) const {
  return static_cast<const unsigned>(std::stoi(this->substr(idx, 1)));
}

std::ostream &operator<<(std::ostream &os, const StrNum &num) {
  if (num.size() <= 3)
    os << static_cast<std::string>(num);
  else {
    const unsigned digits_before_first_comma = num.size() % 3;
    unsigned i = 0;

    // print first digit(s) & first comma
    if (digits_before_first_comma != 0) {
      while (i < digits_before_first_comma) {
        os << num.numAt(i);
        ++i;
      }
      os << ',';
    }

    // print comma after every 3 digits
    unsigned digits_printed = 0;
    while (i < num.size()) {
      os << num.numAt(i);
      ++digits_printed;

      if (digits_printed == 3 and i < num.size() - 3) {
        os << ',';
        digits_printed = 0;
      }

      ++i;
    }
  }

  return os;
}
