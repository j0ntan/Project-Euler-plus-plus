/* Integer right trianlges
 * If p is the perimeter of a right angle triangle with integral
 * length sides, {a,b,c}, there are exactly three solutions for
 * p = 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p ≤ 1000, is the number of solutions
 * maximised? */

#include <iostream>
#include <vector>

bool isRightTriangle(const std::vector<unsigned> &sides);

int main() {
    const unsigned limit = 1000;
    // stores perimeter value and solution count
    std::pair<unsigned,unsigned> maxSolutions{0,0};

    for( auto perim=3u; perim<=limit; ++perim ) {
        std::pair<unsigned,unsigned> thisSolution{perim,0};

        unsigned leg1=1, leg2=1;
        unsigned hypo = perim - leg1 - leg2; // hypotenuse
        std::vector<unsigned> sides{leg1,leg2,hypo};

        while( hypo>0 && leg2<hypo ) {
            while( hypo>0 && leg1<leg2 && leg1<hypo ) {
                if( isRightTriangle(sides) )
                    ++thisSolution.second;
                ++leg1;
                hypo = perim - leg1 - leg2;
                sides = {leg1,leg2,hypo};
            }
            leg1 = 1;
            ++leg2;
            hypo = perim - leg1 - leg2;
            sides = {leg1,leg2,hypo};
        }
        if( thisSolution.second > maxSolutions.second )
            maxSolutions = thisSolution;
    }

    std::cout << "result: "
              << maxSolutions.first
              << std::endl;
}

inline
bool isRightTriangle(const std::vector<unsigned> &sides) {
    return sides[0]*sides[0]
           + sides[1]*sides[1]
           == sides[2]*sides[2];
}
