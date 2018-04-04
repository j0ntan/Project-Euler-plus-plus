/* Sum square difference
 * The sum of the squares of the first ten natural numbers is,
 * 1^2 + 2^2 + ... + 10^2 = 385
 *
 * The square of the sum of the first ten natural numbers is,
 * (1 + 2 + ... + 10)^2 = 55^2 = 3025
 *
 * Hence the difference between the sum of the squares of the first
 * ten natural numbers and the square of the sum is 3025 − 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one
 * hundred natural numbers and the square of the sum. */
#include<iostream>

void primitiveSolution();
void betterSolution();
void evenBetterSolution();

int main() {
    primitiveSolution();
    betterSolution();
    evenBetterSolution();
}

void primitiveSolution() {
    int sumOfSquares=0,sumOfNums=0;
    int i=1;
    do {
        sumOfSquares += i*i;
        sumOfNums += i;
    } while( ++i <= 100 );

    std::cout << "result: " << sumOfNums*sumOfNums - sumOfSquares << std::endl;
}
void betterSolution() {
    /* Based on the analysis where an expansion on (1+2+...+(n-1)+n)
     * results in the sum of each number squared and two times the
     * product of each term with the other terms to the left. The final
     * result requires subtracting each number squared, so what remains
     * is the sum of product terms. */
    int result = 0;
    for( int i=1; i<100; ++i )
        for( int j=i+1; j<=100; ++j )
            result += i*j;
    result *= 2;

    std::cout << "result: " << result << std::endl;
}
void evenBetterSolution() {
    // Based on solution in overview
    int limit = 100;
    int sum = limit*(limit+1)/2;
    int sum_sq = (2*limit+1)*(limit+1)*limit/6;
    std::cout << "result: " << sum*sum - sum_sq << std::endl;
}
