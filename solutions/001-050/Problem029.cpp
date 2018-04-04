/* Distinct powers
 * Consider all integer combinations of a^b for 2 ≤ a ≤ 5
 * and 2 ≤ b ≤ 5:
 *
 *      22=4, 23=8, 24=16, 25=32
 *      32=9, 33=27, 34=81, 35=243
 *      42=16, 43=64, 44=256, 45=1024
 *      52=25, 53=125, 54=625, 55=3125
 *
 * If they are then placed in numerical order, with any
 * repeats removed, we get the following sequence of 15
 * distinct terms:
 *
 *              4, 8, 9, 16, 25, 27, 32, 64, 81,
 *              125, 243, 256, 625, 1024, 3125
 *
 * How many distinct terms are in the sequence generated
 * by a^b for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100? */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

bool compNumStr(const std::string &lhs,
                const std::string &rhs);

std::string nextProduct(const std::string &baseStr, const unsigned &baseNum);

int main() {
    std::vector<std::string> terms;

    // calculate nums and fill vector
    for( auto baseNum=2u; baseNum<=100; ++baseNum ) {
        std::string productStr;
        std::string baseStr = std::to_string(baseNum);
        for( auto j=2u; j<=100; ++j ) {
            baseStr = nextProduct(baseStr,baseNum);
            terms.push_back( baseStr );
        }
    }

    // sort and remove duplicates
    std::sort( terms.begin(),terms.end(), compNumStr );
    auto end = std::unique( terms.begin(), terms.end() );
    auto size = std::distance( terms.begin(),end  );
    terms.resize( static_cast<unsigned>(size) );

    std::cout << "result: " << terms.size()
              << " terms" << std::endl;
}

std::string nextProduct(const std::string &baseStr, const unsigned &baseNum) {
    std::string revProd;    // stores product in reverse

    auto carry1 = 0u;
    auto carry2 = 0u;
    auto productNum = 0u;
    for( auto it=baseStr.rbegin(); it<baseStr.rend(); ++it ) {
        productNum = (*it-'0') * baseNum + 10*carry1 + carry2;
        carry1 = productNum/100;
        carry2 = (productNum - 100*carry1) / 10;
        productNum -= 100*carry1 + 10*carry2;
        revProd.append( std::to_string(productNum) );
    }
    if( carry1 ) {
        revProd.append( std::to_string(carry2) );
        revProd.append( std::to_string(carry1) );
    }
    else if( carry2 )
        revProd.append( std::to_string(carry2) );

    return std::string( revProd.rbegin(),revProd.rend() );
}

bool compNumStr(const std::string &lhs,
                const std::string &rhs) {
    if( lhs.size() == rhs.size() )
        return lhs.compare(rhs) < 0;
    else return lhs.size() < rhs.size();
}

