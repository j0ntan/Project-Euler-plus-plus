/* Triangular, pentagonal, and hexagonal
 * Triangle, pentagonal, and hexagonal numbers are generated by
 * the following formulae:
 * Triangle 	  	T_n=n(n+1)/2 	  	1, 3, 6, 10, 15, ...
 * Pentagonal 	  	P_n=n(3n−1)/2 	  	1, 5, 12, 22, 35, ...
 * Hexagonal 	  	H_n=n(2n−1) 	  	1, 6, 15, 28, 45, ...
 *
 * It can be verified that T285 = P165 = H143 = 40755.
 *
 * Find the next triangle number that is also pentagonal and
 * hexagonal. */

#include <iostream>

unsigned calcHexNum(unsigned num);

unsigned calcTriNum(unsigned num);

unsigned calcPentNum(unsigned num);

int main() {
    // start from indices found
    // in the problem description
    auto triIdx = 285u;
    auto pentIdx = 165u;
    auto hexIdx = 143u;

    auto foundTripleEquiv = false;
    while( !foundTripleEquiv ) {
        auto hexNum = calcHexNum(++hexIdx);
        auto pentNum = 0u;
        do {
            pentNum = calcPentNum(++pentIdx);
        } while( pentNum <= hexNum );
        if( pentNum > hexNum )
            pentNum = calcPentNum(--pentIdx);

        auto triNum =0u;
        do {
            triNum = calcTriNum(++triIdx);
        } while( triNum <= pentNum );
        if( triNum > pentNum )
            triNum = calcTriNum(--triIdx);

        foundTripleEquiv = triNum==hexNum && hexNum==pentNum;
    }

    std::cout << "result: " << calcHexNum(hexIdx) << std::endl;
}

inline
unsigned calcTriNum(unsigned num) {
    return num*(num+1)/2;
}

inline
unsigned calcPentNum(unsigned num) {
    return num*(3*num-1)/2;
}

inline
unsigned calcHexNum(unsigned num) {
    return num*(2*num-1);
}
