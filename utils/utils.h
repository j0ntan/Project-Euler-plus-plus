#include <string>
#include <iostream>
#include <vector>
#include <cmath>

namespace projEuler {
    bool isPalindrome(std::string str) {
        std::string firstHalf, secondHalf;
        std::string rev; // second half, will be reversed
        bool evenDigits = str.size()%2 == 0;

        auto midIdx = str.size()/2;
        firstHalf = str.substr(0,midIdx);
        if( evenDigits )
            rev = str.substr( midIdx, std::string::npos );
        else
            rev = str.substr( midIdx + 1, std::string::npos );

        secondHalf = std::string( rev.rbegin(), rev.rend() );
        return firstHalf == secondHalf;
    }

    bool isPrime(unsigned num) {
        if( num==1 ) return false;
        else if( num<4 ) return true;
        else if( num%2 == 0 ) return false;
        else if( num<9 ) return true;
        else if( num%3 == 0 ) return false;
        else {
            auto r = static_cast<unsigned >
                    ( std::floor(
                    std::sqrt(
                    static_cast<float>(num) ) ) );
            unsigned f = 5;
            while( f<=r ) {
                if( num%f == 0 ) return false;
                if( num%(f+2) == 0 ) return false;
                f += 6;
            }
            return true;
        }
    }

    std::vector<unsigned>
    getPrimesList(unsigned rangeBegin, unsigned rangeEnd) {
        if( rangeBegin < 2 ) {
            std::cerr << "Invalid rangeBegin, "
                      << "changed to begin at 2"
                      << std::endl;
            rangeBegin = 2;
        }

        std::vector<unsigned> primesList;
        for( auto i = rangeBegin; i <= rangeEnd; ++i )
            if( isPrime(i) )
                primesList.push_back(i);

        return primesList;
    }

    std::vector<unsigned>
    getFirstNPrimesList(unsigned num) {
        std::vector<unsigned> primesList;
        for( auto i=2u, count=0u; count<num; ++i )
            if( isPrime(i) ) {
                ++count;
                primesList.push_back(i);
            }

        return primesList;
    }

    template <typename T>
    std::vector<T> getDigits(T num) {
        std::vector<T> digits;
        while( num>0 ) {
            digits.push_back(num%10);
            num /= 10;
        }
        return std::vector<T>(digits.rbegin()
                ,digits.rend());
    }

    template <typename T>
    T combineDigits(const std::vector<T> &digits) {
        T num=0;
        for( auto i=0u; i<digits.size(); ++i )
            num = 10*num + digits[i];
        return num;
    }

    unsigned factorial(unsigned num) {
        auto result=1u;
        if( num==0 || num==1 )
            result = 1;
        else
            do {
                result *= num;
            } while( --num>1 );
        return result;
    }

    unsigned getGCD(unsigned num1, unsigned num2) {
        unsigned temp;
        while( num2!=0 ) {
            temp = num2;
            num2 = num1%num2;
            num1 = temp;
        }
        return num1;
    }

    namespace debug {
        template <typename T>
        void printLastN( const std::vector<T> &vec, unsigned N) {
            std::cout << "Last " << N << " values are: " << std::endl;
            for( auto i=1u; i<=N; ++i )
                std::cout << *(vec.end()-i) << std::endl;
            std::cout << std::endl;
        }
    }
};
