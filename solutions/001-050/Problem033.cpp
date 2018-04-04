/* Digit cancelling fractions
 * The fraction 49/98 is a curious fraction, as an inexperienced
 * mathematician in attempting to simplify it may incorrectly
 * believe that 49/98 = 4/8, which is correct, is obtained by
 * cancelling the 9s.
 *
 * We shall consider fractions like, 30/50 = 3/5, to be trivial
 * examples.
 *
 * There are exactly four non-trivial examples of this type of
 * fraction, less than one in value, and containing two digits in
 * the numerator and denominator.
 *
 * If the product of these four fractions is given in its lowest
 * common terms, find the value of the denominator. */

#include <iostream>
#include <cmath>
#include <vector>
#include "../../utils/utils.h"

bool hasCommonDigit(unsigned num1, unsigned num2);

void testAndRecord(unsigned, unsigned,
        std::vector<std::pair<unsigned,unsigned>> &);

int main() {
    std::vector<std::pair<unsigned,unsigned>> fracs;
    for( auto i=10u; i<99; ++i )
        for( auto j=i+1; j<100; ++j )
            if( hasCommonDigit(i, j) )
                testAndRecord(i,j,fracs);

    unsigned totalNumer=1, totalDenom=1;
    for( auto i=0u; i<fracs.size(); ++i ) {
        totalNumer *= fracs[i].first;
        totalDenom *= fracs[i].second;
    }

    unsigned gcd = projEuler::getGCD(totalNumer,totalDenom);
    std::cout << "result: " << totalDenom/gcd << std::endl;
}

bool hasCommonDigit(unsigned num1, unsigned num2) {
    std::pair<unsigned,unsigned> digits1( num1/10, num1 - num1/10*10 );
    std::pair<unsigned,unsigned> digits2( num2/10, num2 - num2/10*10 );
    return digits1.first==digits2.second ||
           digits1.second==digits2.first;
}

std::pair<unsigned, unsigned>
uncommDigits(unsigned num1, unsigned num2) {
    std::pair<unsigned,unsigned> digits1( num1/10, num1 - num1/10*10 );
    std::pair<unsigned,unsigned> digits2( num2/10, num2 - num2/10*10 );
    unsigned first=0, second=0;
    if( digits1.first==digits2.first ) {
        first = digits1.second;
        second = digits2.second;
    }
    else if( digits1.first==digits2.second ) {
        first = digits1.second;
        second = digits2.first;
    }
    else if( digits1.second==digits2.first ) {
        first = digits1.first;
        second = digits2.second;
    }
    else {
        first = digits1.first;
        second = digits2.first;
    }

    return std::pair<unsigned,unsigned>(first,second);
}

inline
bool fEquiv(float ratio1, float ratio2) {
    return fabs(ratio1-ratio2) < 0.001;
}

void testAndRecord(unsigned numer,
        unsigned denom,
        std::vector<std::pair<unsigned,unsigned>> &fracs) {
    float ratio1 = float(numer) / float(denom);

    auto equivFract = uncommDigits(numer,denom);
    float ratio2 = float(equivFract.first)/
                        float(equivFract.second);

    if( fEquiv(ratio1,ratio2) )
        fracs.push_back(std::pair<unsigned,unsigned>
                (numer,denom) );
}
