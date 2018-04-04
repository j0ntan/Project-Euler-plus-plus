/* Multiples of 3 and 5
 *
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000. */
#include<iostream>

void simpleSolution();
void betterSolution();
int SumDivisibleBy(int n);

int upper_bound = 1000;

int main() {
    //simpleSolution();
    betterSolution();
}

void simpleSolution() {
    int number = 0;
    int sum = 0;

    do {
        if( number%3==0 || number%5==0 )
            sum += number;
    } while ( ++number < upper_bound );

    std::cout << "The final sum is " << sum << std::endl;
}
void betterSolution() {
    // This solution comes from the overview.
    std::cout << "The result is "
              << SumDivisibleBy(3) + SumDivisibleBy(5) - SumDivisibleBy(15) << std::endl;
}
int SumDivisibleBy(int n) {
    int p = (upper_bound-1)/n;
    int result = n * p * (p+1) / 2;
    return result;
}
