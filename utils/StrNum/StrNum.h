#ifndef STRNUM_H
#define STRNUM_H

#include <string>

class StrNum : public std::string {
public:
  explicit StrNum(const unsigned &numerical = 0);
  explicit StrNum(const std::string &str);

  StrNum(const StrNum &) = default;

  const StrNum operator+(const StrNum &rhs) const;
  const StrNum &operator+=(const StrNum &rhs);
  const StrNum operator*(const StrNum &rhs) const;

  const unsigned numAt(unsigned idx) const;
};

#endif // STRNUM_H
