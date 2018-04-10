/* Lychrel numbers
 *
 * If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
 *
 * Not all numbers produce palindromes so quickly. For example,
 *
 * 349 + 943 = 1292,
 * 1292 + 2921 = 4213
 * 4213 + 3124 = 7337
 *
 * That is, 349 took three iterations to arrive at a palindrome.
 *
 * Although no one has proved it yet, it is thought that some numbers, like 196,
 * never produce a palindrome. A number that never forms a palindrome through
 * the reverse and add process is called a Lychrel number. Due to the
 * theoretical nature of these numbers, and for the purpose of this problem, we
 * shall assume that a number is Lychrel until proven otherwise. In addition you
 * are given that for every number below ten-thousand, it will either (i) become
 * a palindrome in less than fifty iterations, or, (ii) no one, with all the
 * computing power that exists, has managed so far to map it to a palindrome. In
 * fact, 10677 is the first number to be shown to require over fifty iterations
 * before producing a palindrome: 4668731596684224866951378664 (53 iterations,
 * 28-digits).
 *
 * Surprisingly, there are palindromic numbers that are themselves Lychrel
 * numbers; the first example is 4994.
 *
 * How many Lychrel numbers are there below ten-thousand? */

#include "../../utils/StrNum/StrNum.h"
#include "../../utils/utils.h"
#include <iostream>

// function prototypes
StrNum reverseDigits(const StrNum &num);

int main() {
  const unsigned NUMBERS_LIMIT = 10'000;
  const unsigned ITERATION_LIMIT = 50;

  unsigned lychrel_number_count = 0;
  for (unsigned number = 0; number < NUMBERS_LIMIT; number++) {
    bool is_palindrome = false;
    StrNum original(number);
    for (unsigned iter_count = 1;
         iter_count < ITERATION_LIMIT and not is_palindrome; iter_count++) {
      StrNum reverse = reverseDigits(original);

      StrNum sum = original + reverse;

      is_palindrome = projEuler::isPalindrome(sum);

      original = sum;
    }
    if (not is_palindrome)
      lychrel_number_count++;
  }

  std::cout << "There are " << lychrel_number_count
            << " Lychrel numbers below ten-thousand.";
}

StrNum reverseDigits(const StrNum &num) {
  StrNum reversed(num);

  const unsigned num_swaps = reversed.size() / 2;
  for (unsigned i = 0; i < num_swaps; ++i)
    std::swap(reversed[i], reversed[reversed.size() - i - 1]);

  return reversed;
}

/* Thought process:
 * 1. According to the problem statement, we have an upper-bound of 50
 * iterations to try the "reverse and add" process to get a palindromic number.
 * To solve this problem, we must try the "reverse and add" process, for numbers
 * in the range of [0,1e4), and count the number of times we cannot get a
 * palindrome before 50 iterations of the process.
 * 2. The problem statement refers to a 28-digit palindrome resulting from the
 * number 10677. This suggests that we will possibly have to deal with very
 * large numbers during the process of finding a palindrome. Thus, it is a good
 * idea to use a string-based representation of numbers, used in solutions to
 * previous problems, to avoid issues with overflow for large numbers. */
