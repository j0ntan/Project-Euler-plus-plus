/* Passcode derivation
 * A common security method used for online banking is to ask the user for three
 * random characters from a passcode. For example, if the passcode was 531278,
 * they may ask for the 2nd, 3rd, and 5th characters; the expected reply would
 * be: 317.
 *
 * The text file, keylog.txt, contains fifty successful login attempts.
 *
 * Given that the three characters are always asked for in order, analyse the
 * file so as to determine the shortest possible secret passcode of unknown
 * length. */

#include "../../utils/StrNum/StrNum.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

// function prototypes
std::vector<StrNum> readKeylog(const char *filename);
void sortAndRemoveDuplicates(std::vector<StrNum> &keys);

int main() {
  StrNum passcode;
  auto keys =
      readKeylog("../../../solutions/051-100/Problem079/p079_keylog.txt");

  sortAndRemoveDuplicates(keys);

  std::cout << "Passcode is " << passcode;
}

std::vector<StrNum> readKeylog(const char *filename) {
  std::ifstream file(filename);
  if (file.fail()) {
    std::cerr << "Failed to open the file" << std::endl;
    exit(1);
  }

  StrNum line;
  std::vector<StrNum> keys;
  keys.reserve(50);

  while (file.good()) {
    std::getline(file, line);
    keys.push_back(line);
  }

  keys.pop_back(); // remove empty string that was stored from EOF

  return keys;
}

void sortAndRemoveDuplicates(std::vector<StrNum> &keys) {
  std::sort(keys.begin(), keys.end());
  auto new_end = std::unique(keys.begin(), keys.end());
  keys.erase(new_end, keys.end());
}

bool containsKey(const StrNum &key, const StrNum &passcode) {
  const auto first_location =
      std::find(passcode.cbegin(), passcode.cend(), key[0]);
  const auto second_location =
      std::find(first_location, passcode.cend(), key[1]);
  const auto third_location =
      std::find(second_location, passcode.cend(), key[2]);
  return first_location != passcode.cend() and
         second_location != passcode.cend() and
         third_location != passcode.cend();
}

bool containsUnorderedKey(const StrNum &missing_key, const StrNum &passcode) {
  const bool found_first = std::find(passcode.cbegin(), passcode.cend(),
                                     missing_key[0]) != passcode.cend();
  const bool found_second = std::find(passcode.cbegin(), passcode.cend(),
                                      missing_key[1]) != passcode.cend();
  const bool found_third = std::find(passcode.cbegin(), passcode.cend(),
                                     missing_key[2]) != passcode.cend();
  return found_first and found_second and found_third;
}

bool rangeOfKeysValid(const StrNum &passcode,
                      const std::vector<StrNum>::const_iterator &first_key_it,
                      const std::vector<StrNum>::const_iterator &last_key_it) {
  auto this_key_it = first_key_it;
  bool all_keys_valid = true;
  while (all_keys_valid and this_key_it != last_key_it + 1) {
    all_keys_valid = containsKey(*this_key_it, passcode);
    ++this_key_it;
  }
  return all_keys_valid;
}

/* First thoughts
 * 1. This problem requires storing and updating the passcode as we look at each
 * new key. The passcode must be valid for every key in the file. This means
 * that the relative positions of the digits in the key must be found within the
 * passcode. If it is not found, we must update the passcode so that it becomes
 * valid for that particular key.
 * 2. This problem  becomes easier to analyze if we sort the keys and remove any
 * duplicates.
 * 3. If the entire sequence is not found within the passcode, we can just add
 * those digits to the end of the passcode. */
