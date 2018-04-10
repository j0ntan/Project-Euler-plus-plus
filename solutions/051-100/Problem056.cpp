/* A googol (10^100) is a massive number: one followed by one-hundred zeros;
 * 100^100 is almost unimaginably large: one followed by two-hundred zeros.
 * Despite their size, the sum of the digits in each number is only 1.
 *
 * Considering natural numbers of the form, ab, where a, b < 100, what is the
 * maximum digital sum? */

int main() {
  //
}

/* Thought process:
 * 1. With the given range, a brute force check of all possible numbers is not
 * practical.
 * 2. We can expect very large numbers, thus a string-based representation of
 * integers is necessary here.
 * 3. For this problem, we want to calculate the larger numbers rather than any
 * of the smaller numbers for large sum-of-digits value.
 * 4. It is given that 100^100 has two-hundred zeros. The given bounds is for
 * a,b < 100. Thus, in a best-case scenario, we can have a number with
 * two-hundred digits of the number nine. In this case, the sum-of-digits is
 * 9 * 200 = 1800, which can fit in a variable of integer type. */
