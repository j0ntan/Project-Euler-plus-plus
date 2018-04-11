/* Pentagon number
 * Pentagonal numbers are generated by the formula, P_n = n(3n − 1) / 2. The
 * first ten pentagonal numbers are:
 *
 *                 1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
 *
 * It can be seen that P_4 + P_7 = 22 + 70 = 92 = P_8. However, their
 * difference, 70 − 22 = 48, is not pentagonal.
 *
 * Find the pair of pentagonal numbers, P_j and P_k, for which their sum and
 * difference are pentagonal and D = |P_k − P_j| is minimised; what is the
 * value of D? */

int main() {
}

/* Thought process
 * 1. The old solution attempt was using a brute-force approach, but was not
 * well implemented. More analysis was needed.
 * 2. The previous attempt used a linear search to determine whether or not a
 * given number is pentagonal. A better way to check this comes from the
 * equation for pentagonal numbers. If we solve for n, using the quadratic
 * equation, we obtain n = [1 ± sqrt(1 + 24*P_n)] / 6. The number n must be
 * positive, thus we have that n = [1 + sqrt(1 + 24*P_n)] / 6. In addition, n
 * must be an integer. Thus, a given number, P_n, is pentagonal if the solution
 * to the quadratic equation is an integer. */
