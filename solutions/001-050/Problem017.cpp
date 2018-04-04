/* Number letter counts
 * If the numbers 1 to 5 are written out in words: one, two, three, four,
 * five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 *
 * If all the numbers from 1 to 1000 (one thousand) inclusive were
 * written out in words, how many letters would be used?
 *
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred
 * and forty-two) contains 23 letters and 115 (one hundred and fifteen)
 * contains 20 letters. The use of "and" when writing out numbers is in
 * compliance with British usage. */

#include <iostream>
#include <cstring>

unsigned &&countSubHundred();

int main() {
    unsigned lettersCount =0u;

    // get the sum for 1-99
    lettersCount += countSubHundred();

    unsigned singleDigits[] = {3,3,5,4,4,3,5,5,4};
    for( auto i=0u; i<9; ++i )
        lettersCount += singleDigits[i]                 // 100,200,...,900
                      + strlen("hundred");

    for( auto i=0u; i<9; ++i )                          // 101,...199,201,...299,...999
        lettersCount += 99*( singleDigits[i]            // x 'hundred and' y
                             + strlen("hundred")
                             + strlen("and") )
                      + countSubHundred();

    lettersCount += 3 + 8;                              // 1000

    std::cout << "result: " << lettersCount << std::endl;
}

unsigned &&countSubHundred() {
    unsigned singleDigits[] = {3,3,5,4,4,3,5,5,4};
    unsigned tens[9]        = {3,6,6,5,5,5,7,6,6};
    unsigned teens[9]       = {6,6,8,8,7,7,9,8,8};

    unsigned count=0;

    for(auto i=0u; i<9; ++i ) {
        count += singleDigits[i];           // 1-9
        count += tens[i];                   // 10,20,30,...,90
        count += teens[i];                  // 11-19
    }

    for( auto i=1u; i<9; ++i )              // 21-29,31-39,...,91-99
        for( auto j=0u; j<9; ++j )
            count += tens[i] + singleDigits[j];

    return std::move(count);
}