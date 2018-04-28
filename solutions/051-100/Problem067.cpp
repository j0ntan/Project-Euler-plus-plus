/* Maximum path sum II
 * By starting at the top of the triangle below and moving to adjacent numbers
 * on the row below, the maximum total from top to bottom is 23.
 *
 *                                     3
 *                                    7 4
 *                                   2 4 6
 *                                  8 5 9 3
 *
 * That is, 3 + 7 + 4 + 9 = 23.
 *
 * Find the maximum total from top to bottom in triangle.txt (right click and
 * 'Save Link/Target As...'), a 15K text file containing a triangle with
 * one-hundred rows.
 *
 * NOTE: This is a much more difficult version of Problem 18. It is not possible
 * to try every route to solve this problem, as there are 2^99 altogether! If
 * you could check one trillion (10^12) routes every second it would take over
 * twenty billion years to check them all. There is an efficient algorithm to
 * solve it. ;o) */

#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

// function prototypes
std::ifstream openFile(const std::string &filename);
unsigned readNum(std::ifstream &file);
std::pair<unsigned, unsigned> readAdjacentNums(std::ifstream &file,
                                               unsigned index);

int main() {
  auto file =
      openFile("../../../solutions/051-100/Problem067/p067_triangle.txt");
  std::vector<unsigned> path_nums(100, 0);
  unsigned path_num_index = 0;
  path_nums[path_num_index] = readNum(file);

  for (unsigned row = 1; row < 100; ++row) {
    const auto adjacent_nums = readAdjacentNums(file, path_num_index);
    if (adjacent_nums.first > adjacent_nums.second)
      path_nums[row] = adjacent_nums.first;
    else {
      path_nums[row] = adjacent_nums.second;
      ++path_num_index;
    }
  }

  std::cout << "Maximum path sum is "
            << std::accumulate(path_nums.begin(), path_nums.end(), 0);
}

std::ifstream openFile(const std::string &filename) {
  std::ifstream file(filename);

  if (file.fail()) {
    std::cerr << "Could not open the file" << std::endl;
    exit(1);
  }

  return file;
}

unsigned readNum(std::ifstream &file) {
  // remove whitespace
  while (file.peek() == ' ' or file.peek() == '\n')
    file.get();

  // read both digits
  char first_digit, second_digit;
  file.get(first_digit);
  file.get(second_digit);

  std::string num_str;
  if (first_digit == '0')
    num_str.push_back(second_digit);
  else
    num_str.append({first_digit, second_digit});

  return static_cast<unsigned>(std::stoi(num_str));
}

std::pair<unsigned, unsigned> readAdjacentNums(std::ifstream &file,
                                               unsigned index) {
  // read and discard non-adjacent numbers
  for (unsigned i = 0; i < index; ++i)
    readNum(file);

  const unsigned adjacent_left = readNum(file);
  const unsigned adjacent_right = readNum(file);

  // read and discard everything else on the row
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  return std::make_pair(adjacent_left, adjacent_right);
}

/* First thoughts
 * 1. My previous implementation for Problem 18 is a bit hard to read, so this
 * problem provides a chance to build a better written and better thought-out
 * solution.
 * 2. We can observe that for any row containing n numbers, the next row below
 * contains n+1 numbers. In addition, for any number in a row with index i, the
 * adjacent numbers in the row below will have an index of i or i+1,
 * corresponding to the left-adjacent or right-adjacent number, respectively.
 * 3. To traverse the path with a maximum sum, we begin at the top. As we look
 * at the next row and further, we only need to consider the adjacent numbers
 * and can ignore the rest of the numbers on that row. So we can just take the
 * larger of the adjacent numbers, and move on to the next row, continuing in
 * the same fashion until we reach the bottom.
 * 4. After getting a wrong answer, we debug and verify that the functions used
 * are working correctly. This indicates that there is a problem with the
 * algorithm used. Upon looking at other solutions and approaches, we can
 * conclude that there was an initial misunderstanding of the problem. It is not
 * enough to look at the maximum of the adjacent numbers because another route
 * may contain larger numbers in the rows further below. This problem requires a
 * dynamic programming solution, which first requires a better understanding of
 * dynamic programming in general. */
