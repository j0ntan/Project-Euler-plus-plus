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
#include <vector>

int main() {
  //
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
 * */
