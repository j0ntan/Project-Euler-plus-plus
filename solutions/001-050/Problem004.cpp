/* Largest palindrome product
 * A palindromic number reads the same both ways. The largest palindrome made from the
 * product of two 2-digit numbers is 9009 = 91 x 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers. */
#include<iostream>
#include<cmath>

void primitiveSolution();
void stringSolution();
void betterSolution();

int main() {
    //primitiveSolution();
    //stringSolution();
    betterSolution();
}

void primitiveSolution() {
    int firstNum = 0;
    int secondNum = 0;
    int product;
    int palindrome=0;
    int digit1,digit2,digit3,digit4,digit5,digit6;

    for( int i=100; i<999; ++i ) {
        for( int j=i; j<999; ++j ) {
            product = i*j;
            if( product<10000 ) {
                digit1 = (product - product/int(pow(10,5))*int(pow(10,5)))/int(pow(10,4));
                digit2 = (product - product/int(pow(10,4))*int(pow(10,4)))/int(pow(10,3));
                digit4 = (product - product/int(pow(10,2))*int(pow(10,2)))/int(pow(10,1));
                digit5 = (product - product/int(pow(10,1))*int(pow(10,1)))/int(pow(10,0));

                if( digit1==digit5 && digit2==digit4 && product>palindrome ) {
                    firstNum = i;
                    secondNum = j;
                    palindrome = product;
                }
            }
            else {
                digit1 = (product - product/int(pow(10,6))*int(pow(10,6)))/int(pow(10,5));
                digit2 = (product - product/int(pow(10,5))*int(pow(10,5)))/int(pow(10,4));
                digit3 = (product - product/int(pow(10,4))*int(pow(10,4)))/int(pow(10,3));
                digit4 = (product - product/int(pow(10,3))*int(pow(10,3)))/int(pow(10,2));
                digit5 = (product - product/int(pow(10,2))*int(pow(10,2)))/int(pow(10,1));
                digit6 = (product - product/int(pow(10,1))*int(pow(10,1)))/int(pow(10,0));

                if( digit1==digit6 && digit2==digit5 && digit3==digit4 && product>palindrome ) {
                    firstNum = i;
                    secondNum = j;
                    palindrome = product;
                }
            }
        }
    }

    std::cout << palindrome << " = " << firstNum << " x " << secondNum << std::endl;
}
void stringSolution() {
    std::string num, palindrome = "0";
    bool found_p = false;
    int num1=0, num2=0;

    for( int i=100; i<999; ++i ) {
        for( int j=i; j<999; ++j ) {
            num = std::to_string(i*j);

            // start comparing digits
            found_p = true;
            int digits = num.size();
            for( int i=0; i<digits/2; ++i )
                if( num[i] != num[digits-1-i] ) {
                    found_p = false;
                    break;
                }

            if( found_p && std::stoi(num) > std::stoi(palindrome) ) {
                palindrome = num;
                num1 = i;
                num2 = j;
            }
        }
    }
    std::cout << "result: " << palindrome  << " = " << num1 << " x " << num2 << std::endl;
}
int reverse(int n) {
    int reversed = 0;
    while( n > 0 ) {
        reversed = 10*reversed + n%10;
        n /= 10;
    }
    return reversed;
}
bool isPalindrome(int n) {
    return n == reverse(n);
}
void betterSolution() {
    // Based on overview solution.
    int largestPalindrome = 0;
    int a = 999;
    int b, db;
    do {
        if( a%11 == 0 ) {
            b = 999;
            db = 1;
        }
        else {
            b = 990;
            db = 11;
        }
        do {
            if( a*b <= largestPalindrome ) break;
            if( isPalindrome(a*b) ) largestPalindrome = a*b;
            b = b - db;
        } while( b >= a);
    } while( --a >= 100 );

    std::cout << "result: " << largestPalindrome << std::endl;
}
