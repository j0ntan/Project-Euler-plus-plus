/* Lexicographic permutations
 * A permutation is an ordered arrangement of objects. For example,
 * 3124 is one possible permutation of the digits 1, 2, 3 and 4. If
 * all of the permutations are listed numerically or alphabetically,
 * we call it lexicographic order. The lexicographic permutations of
 * 0, 1 and 2 are:
 *
 *                 012   021   102   120   201   210
 *
 * What is the millionth lexicographic permutation of the digits
 * 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9? */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<short> digits;

    // initialize vector with individual digits
    for( short i=0; i<10; ++i ) digits.push_back(i);

    // get permutations
    for( auto i=1u; i<1000000; ++i )
        std::next_permutation( digits.begin(),digits.end() );

    std::ostream_iterator<short> output(std::cout,nullptr);
    std::cout << "result: ";
    std::copy(digits.begin(),digits.end(),output);
}