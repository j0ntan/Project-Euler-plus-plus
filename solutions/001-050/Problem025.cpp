/* 1000-digit Fibonacci number
 * The Fibonacci sequence is defined by the recurrence relation:
 *
 * F_n = F_n−1 + F_n−2, where F_1 = 1 and F_2 = 1.
 *
 * Hence the first 12 terms will be:
 *
 * F_1 = 1
 * F_2 = 1
 * F_3 = 2
 * F_4 = 3
 * F_5 = 5
 * F_6 = 8
 * F_7 = 13
 * F_8 = 21
 * F_9 = 34
 * F_10 = 55
 * F_11 = 89
 * F_12 = 144
 *
 * The 12th term, F_12, is the first term to contain three digits.
 *
 * What is the index of the first term in the Fibonacci sequence
 * to contain 1000 digits? */

#include <iostream>

std::string nextFibNum(std::string &prev1, std::string &prev2);

int main() {
    // F_n-2, F_n-1, F_n, respectively
    std::string prev1, prev2, curr;
    prev1 = prev2 = "1";
    auto idx = 2;

    while(
            //idx < 100 ) {
            curr.size() != 1000 ) {
        curr = nextFibNum(prev1,prev2);
        ++idx;
    }

    std::cout << "result: " << idx <<std::endl;
}

std::string sum(const std::string &num1, const std::string &num2) {
    std::string sum_str;
    auto digit1=0u, digit2=0u, digit_sum=0u;
    auto sum=0u, carry=0u;

    for( auto i=0u; i<num1.size(); ++i ) {
        digit1 = static_cast<unsigned>( num1[i]-'0' );
        digit2 = static_cast<unsigned>( num2[i]-'0' );
        sum = digit1 + digit2 + carry;      // max is 18 (9+9)
        carry = sum/10;                     //either 0 or 1
        digit_sum = sum - 10*carry;
        sum_str.append( std::to_string(digit_sum) );
    }
    if( num1.size() == num2.size() && carry )
        sum_str.append( "1" );
    else if( num2.size() > num1.size() ) {
        sum = num2.back()-'0'+carry;
        sum_str.append( std::to_string(sum) );
    }

    return sum_str;
}

std::string nextFibNum(std::string &prev1, std::string &prev2) {
    std::string fibNum = sum(prev1,prev2);

    prev1 = prev2;
    prev2 = fibNum;

    return fibNum;
}