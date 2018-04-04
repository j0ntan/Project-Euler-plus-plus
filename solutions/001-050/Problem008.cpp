/* Largest product in a series
 * The four adjacent digits in the 1000-digit number that have the
 * greatest product are 9 x 9 x 8 x 9 = 5832.
 *
 * 73167176531330624919225119674426574742355349194934
 * 96983520312774506326239578318016984801869478851843
 * 85861560789112949495459501737958331952853208805511
 * 12540698747158523863050715693290963295227443043557
 * 66896648950445244523161731856403098711121722383113
 * 62229893423380308135336276614282806444486645238749
 * 30358907296290491560440772390713810515859307960866
 * 70172427121883998797908792274921901699720888093776
 * 65727333001053367881220235421809751254540594752243
 * 52584907711670556013604839586446706324415722155397
 * 53697817977846174064955149290862569321978468622482
 * 83972241375657056057490261407972968652414535100474
 * 82166370484403199890008895243450658541227588666881
 * 16427171479924442928230863465674813919123162824586
 * 17866458359124566529476545682848912883142607690042
 * 24219022671055626321111109370544217506941658960408
 * 07198403850962455444362981230987879927244284909188
 * 84580156166097919133875499200524063689912560717606
 * 05886116467109405077541002256983155200055935729725
 * 71636269561882670428252483600823257530420752963450
 *
 * Find the thirteen adjacent digits in the 1000-digit number that
 * have the greatest product. What is the value of this product? */

#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

typedef long long int Bignum;

Bignum readNum(int pos, std::ifstream &);
void simpleSolution();
void showProblem();

int main() {
    simpleSolution();
    //showProblem();
}

void simpleSolution() {
    // open the file containing the monstrous 1000 digit number
    std::ifstream file;
    file.open("../../../solutions/001-050/Problem008/longnum.txt");
    if( file.fail() ) {
        std::cout << "error opening the file. exiting" << std::endl;
        exit(1);
    }

    std::vector<Bignum> digits(13, 0);
    auto max_digits = digits;

    Bignum prod1=0, prod2=0;
    for( int i=0; i<1000-13+1; ++i ) {
        prod1 = 1;
        for( int j=0; j<13; ++j ) {
            digits[j] = readNum(i+j,file);
            prod1 *= digits[j];
        }
        if( prod1 > prod2 ) {
            max_digits = digits;
            prod2 = prod1;
        }
    }
    file.close();

    std::cout << "result: " << prod2 << std::endl;
    //for( int i=0; i<13; ++i ) std::cout << max_digits[i] << ' '; std::cout << std::endl;
}
Bignum readNum(int pos, std::ifstream &file) {
    pos += (pos/50)*2;   // modify due to CR LF
    char digit = static_cast<char>( file.seekg(pos).get() );
    return static_cast<Bignum>( digit - '0' );
}
void showProblem() {
    long long a[13] = {5,5,7,6,6,8,9,6,6,4,8,9,5}, product = 1;
    std::vector<long long> v;
    for( int i=0; i<13; ++i ) {
        v.push_back( a[i] );
        product *= a[i];
    }
    std::cout << "result1: "
              << std::accumulate(v.begin(),v.begin()+13,1, std::multiplies<long long>())
              << std::endl;
    std::cout << "result2: " << product << std::endl;
}
