/* Number spiral diagonals
 * Starting with the number 1 and moving to the right in a
 * clockwise direction a 5 by 5 spiral is formed as follows:
 *
 *                      21 22 23 24 25
 *                      20  7  8  9 10
 *                      19  6  1  2 11
 *                      18  5  4  3 12
 *                      17 16 15 14 13
 *
 * It can be verified that the sum of the numbers on the
 * diagonals is 101.
 *
 * What is the sum of the numbers on the diagonals in a 1001
 * by 1001 spiral formed in the same way? */

#include <iostream>
#include <vector>
#include <numeric>

std::vector<unsigned> getCorners(unsigned size);

int main() {
    /* By writing out the spiral, we can make observations
     * on the corners of each a_n x a_n spiral. We see that
     * the spiral grows by adding one row or column around
     * the previous spiral, effectively increasing a n x n
     * spiral to a (n+2)x(n+2) spiral each time. The pattern
     * observed is summarized in the table below.
     *
     *  Spiral |   UR  |   LR  |   UL  |   LL  |
     * --------|-------|-------|-------|-------|
     *    3X3  |  3^2  | 3*1-0 | 3^2-2 | 3*1+2 |
     *         |  = 9  |  = 3  |  = 7  |  = 5  |
     *    5X5  |  5^2  | 5*3-2 | 5^2-4 | 5*3+2 |
     *         |  = 25 |  = 13 |  = 21 |  = 17 |
     *    7X7  |  7^2  | 7*5-4 | 7^2-6 | 7*5+2 |
     *         |  = 49 |  = 31 |  = 43 |  = 37 |
     *    9X9  |  9^2  | 9*7-6 | 9^2-8 | 9*7+2 |
     *         |  = 81 |  = 57 |  = 73 |  = 65 |
     *    ...  |       |       |       |       |
     *
     *   where
     *   UR = upper right corner
     *      calculation: a_n^2
     *   LR = lower right corner
     *      calculation: a_n*a_n-1 - (a_n-1 - 1)
     *   UL = upper left corner
     *      calculation: a_n^2 - (a_n - 1)
     *   LL = lower left corner
     *      calculation: a_n*a_n-1 + 2
     *   and a_n is current spiral size and a_n-1
     *   is previous spiral size. */

    // calculate and store corner values
    // for a_n x a_n spirals
    std::vector<unsigned> allCorners(1,1); // begin with center
    std::vector<unsigned> currentCorners;
    for( auto i=3u; i<=1001; i+=2 ) {
        currentCorners = getCorners(i);
        allCorners.insert( allCorners.end(),
                           currentCorners.begin(),
                           currentCorners.end() );
    }

    std::cout << "result: "
              << std::accumulate( allCorners.begin(),
                                  allCorners.end(),
                                  0u );
}

std::vector<unsigned> getCorners(unsigned size) {
    static std::vector<unsigned> result(4,0);
    result[0] = size*size;
    result[1] = size*(size-2) - (size-2 - 1);
    result[2] = size*size - (size - 1);
    result[3] = size*(size-2) + 2;
    return result;
}