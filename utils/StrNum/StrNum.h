#ifndef STRNUM_H
#define STRNUM_H

#include <iostream>
#include <string>

class StrNum : public std::string {
public:
  explicit StrNum(const unsigned &numerical = 0);
  explicit StrNum(const std::string &str);

  StrNum(const StrNum &) = default;

  bool operator<(const StrNum &rhs) const;
  bool operator==(const StrNum &rhs) const;
  bool operator<=(const StrNum &rhs) const;
  const StrNum operator+(const StrNum &rhs) const;
  const StrNum operator-(const StrNum &rhs) const;
  const StrNum &operator+=(const StrNum &rhs);
  const StrNum &operator-=(const StrNum &rhs);
  const StrNum operator*(const StrNum &rhs) const;
  const StrNum operator/(const StrNum &rhs) const;
  const StrNum operator%(const StrNum &rhs) const;

  const unsigned numAt(unsigned idx) const;

  friend std::ostream &operator<<(std::ostream &os, const StrNum &num);
};

#endif // STRNUM_H
