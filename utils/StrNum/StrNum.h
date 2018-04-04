#ifndef STRNUM_H
#define STRNUM_H


class StrNum : public std::string {
public:
    StrNum(unsigned init=0);
    StrNum(std::string str) : std::string(str){}

    const unsigned operator [](unsigned idx) const;
    const StrNum operator +(const StrNum& rhs) const;
    const StrNum operator *(const unsigned num) const;
    const StrNum operator *(const StrNum& rhs) const;

};


#endif //STRNUM_H
