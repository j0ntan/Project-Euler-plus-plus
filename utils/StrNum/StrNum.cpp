#include <string>
#include "StrNum.h"

StrNum::StrNum(unsigned init)
        : std::string( std::to_string(init) ) {}

const unsigned StrNum::operator[](unsigned idx) const {
    std::string s(*this);
    return static_cast<const unsigned>(s[idx]-'0');
}

const StrNum StrNum::operator+(const StrNum &rhs) const {
    const StrNum *s1 = this;
    const StrNum *s2 = &rhs;
    if( this->size() < rhs.size() )
        std::swap(s1,s2);

    std::string sum;
    auto carry = 0u;
    for( auto i = s1->size()-1u, j = s2->size()-1u
            ; j >= 0 && j < s2->size(); --i,--j ) {
        auto sum_digit = (*s1)[i] + (*s2)[j] + carry;
        carry = sum_digit / 10;
        sum_digit -= 10*carry;
        sum.push_back( static_cast<char>('0'+sum_digit) );
    }
    for( auto i = s1->size() - s2->size() - 1
            ; i >= 0 && i < s1->size(); --i ) {
        auto sum_digit = (*s1)[i] + carry;
        carry = sum_digit / 10;
        sum_digit -= 10*carry;
        sum.push_back( static_cast<char>('0'+sum_digit) );
    }
    if( carry )
        sum.push_back( static_cast<char>('0'+carry) );

    return std::string(sum.rbegin(),sum.rend());
}

const StrNum StrNum::operator*(const unsigned num) const {
    std::string product;
    auto carry = 0u;
    for( auto i = this->size()-1
            ; i >= 0 && i < this->size(); --i ) {
        auto digit = num * (*this)[i] + carry;
        carry = digit / 10;
        digit -= 10 * carry;
        product.push_back( static_cast<char>('0'+digit) );
    }
    if( carry != 0 )
        product.push_back( static_cast<char>('0'+carry) );
    return std::string( product.rbegin(),product.rend() );
}

const StrNum StrNum::operator*(const StrNum &rhs) const {
    const StrNum *s1 = this;
    const StrNum *s2 = &rhs;
    if( this->size() < rhs.size() )
        std::swap(s1,s2);

    StrNum product;
    for( auto i = s2->size() - 1
            ; i >= 0 && i < s2->size(); --i ) {
        StrNum oneDigitProduct = *this * (*s2)[i];

        for( auto j=i+1; j<s2->size(); ++j )
            oneDigitProduct.push_back('0');
        product = product + oneDigitProduct;
    }

    return product;
}