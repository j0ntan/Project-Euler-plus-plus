/* Special Pythagorean triplet
 * A Pythagorean triplet is a set of three natural numbers,
 * a < b < c, for which,
 *
 *                  a^2 + b^2 = c^2
 *
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
 *
 * There exists exactly one Pythagorean triplet for which
 * a + b + c = 1000.
 * Find the product abc. */

#include<iostream>
#include<cmath>

void simpleSolution();

int main() {
    simpleSolution();
}

void simpleSolution() {
    unsigned a=0,b=0;
    double c=0;
    for( b=1;b<=500;++b)
        for( a=1;a<b;++a ) {
            c = sqrt(a*a+b*b);
            if( c-floor(c)==0 && a+b+c==1000) {
                std::cout << a << " " << b << " " << c << std::endl;
                std::cout << "result: " << static_cast<int>( a*b*c );
                return;
            }
        }
}
