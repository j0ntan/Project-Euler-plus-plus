/* Concealed Square
 * Find the unique positive integer whose square has the form
 * 1_2_3_4_5_6_7_8_9_0, where each "_" is a single digit. */

#include <iostream>
#include <string>

typedef unsigned long long ull;

bool hasTargetForm(const std::string &num) {
  return num.size() == 19 and
         (num[2] == '2' and num[4] == '3' and num[6] == '4' and
          num[8] == '5' and num[10] == '6' and num[12] == '7' and
          num[14] == '8' and num[16] == '9');
}

int main() {
  const ull UPPER_LIMIT = 1'389'026'624;
  const ull LOWER_LIMIT = 1'010'101'010;

  for (ull num = LOWER_LIMIT; num <= UPPER_LIMIT; num += 10)
    if (hasTargetForm(std::to_string(num * num))) {
      std::cout << "Root is " << num << std::endl;
      std::cout << "Squared term is " << num * num << std::endl;
      break;
    }
}

/* First thoughts
 * 1. We can limit the numbers to try by replacing all the underscores with a 9
 * or 0. The upper limit is ceiling( sqrt(1929394959697989990) ) = 1389026624.
 * The lower limit is floor( sqrt(1020304050607080900) ) = 1010101010.
 * 2. First attempt took too long and was ended before finding a solution. One
 * improvement can be made on the observation that the squared term must end
 * with a zero digit. This requires that the root term be a multiple of ten.
 * Thus, we can increment by 10 instead of 1 inside the loop. */
