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

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <list>
#include <string>
#include <vector>

class Sequence : public std::list<unsigned> {
public:
  Sequence() = default;
  Sequence(const std::initializer_list<unsigned> &il) : list<unsigned>(il) {}
  bool operator==(const Sequence &rhs) const {
    return static_cast<std::list<unsigned>>(*this) ==
           static_cast<std::list<unsigned>>(rhs);
  }
  bool operator<(const Sequence &rhs) const {
    return static_cast<std::list<unsigned>>(*this) <
           static_cast<std::list<unsigned>>(rhs);
  }
};

class Key {
public:
  explicit Key(const std::string &key_str) {
    if (key_str.length() == 3 && std::isdigit(key_str[0]) != 0 &&
        std::isdigit(key_str[1]) != 0 && std::isdigit(key_str[2]) != 0) {
      digits.emplace_back(key_str[0] - '0');
      digits.emplace_back(key_str[1] - '0');
      digits.emplace_back(key_str[2] - '0');
    } else {
      std::cerr << "Could not construct a key out of the string: " << key_str
                << std::endl;
      exit(1);
    }
  }
  bool operator==(const Key &rhs) const { return this->digits == rhs.digits; }
  bool operator<(const Key &rhs) const { return this->digits < rhs.digits; }
  Sequence::const_iterator begin() const { return digits.begin(); }
  Sequence::const_iterator end() const { return digits.end(); }
  Sequence::const_iterator cbegin() const { return digits.cbegin(); }
  Sequence::const_iterator cend() const { return digits.cend(); }

private:
  Sequence digits;
};

class Keys : public std::vector<Key> {};

class Passcode {
public:
  typedef std::pair<unsigned, Sequence> Valid_Digit_t;

  explicit Passcode(const Key &key) {
    auto current_digit_it = key.cbegin();
    auto next_digit_it = current_digit_it;
    ++next_digit_it;
    digits.emplace_back(
        std::make_pair(*current_digit_it++, Sequence{*next_digit_it++}));
    digits.emplace_back(
        std::make_pair(*current_digit_it++, Sequence{*next_digit_it++}));
    digits.emplace_back(std::make_pair(*current_digit_it, Sequence{}));
  }

  bool containsKey(const Key &key) const {
    auto last_found_digit_it = digits.cbegin();
    for (const auto &digit : key)
      last_found_digit_it = std::find_if(
          last_found_digit_it, digits.cend(),
          [&](const Valid_Digit_t &vd) { return vd.first == digit; });
    return last_found_digit_it != digits.cend();
  }
  bool containsUnorderedKey(const Key &key) const {
    bool all_digits_found = true;
    for (const auto &digit : key) {
      const auto digit_location_it = std::find_if(
          digits.cbegin(), digits.cend(),
          [&](const Valid_Digit_t &vd) { return vd.first == digit; });
      if (digit_location_it == digits.cend())
        all_digits_found = false;
    }
    return all_digits_found;
  }
  bool rangeOfKeysValid(const Keys::const_iterator &first_key_it,
                        const Keys::const_iterator &last_key_it) {
    auto this_key_it = first_key_it;
    bool all_keys_valid = true;
    if (first_key_it != last_key_it)
      while (all_keys_valid and this_key_it != last_key_it + 1)
        all_keys_valid = containsKey(*this_key_it++);
    else
      all_keys_valid = false;
    return all_keys_valid;
  }
  void insertKeyDigits(const Key &missing_key) {
    auto last_found_it = digits.begin();
    for (auto digit_it = missing_key.cbegin(); digit_it != missing_key.cend();
         ++digit_it) {
      auto found_current_digit_it = std::find_if(
          last_found_it, digits.end(),
          [&](const Valid_Digit_t &vd) { return vd.first == *digit_it; });
      if (found_current_digit_it == digits.end()) {
        if (digit_it == missing_key.cbegin())
          digits.insert(last_found_it, std::make_pair(*digit_it, Sequence()));
        else
          digits.insert(++last_found_it, std::make_pair(*digit_it, Sequence()));
        --last_found_it;
      } else
        last_found_it = found_current_digit_it;
    }
  }
  void validateNewKey(const Keys::const_iterator &first_key_it,
                      const Keys::const_iterator &last_key_it) {
    const auto &new_key = *last_key_it;
    if (not containsKey(new_key)) {
      bool key_validated = false;
      if (containsUnorderedKey(new_key)) {
        // TODO: implement passcode rearrangement
        /*
        auto new_passcode = rearrangePasscode(first_key_it, last_key_it);
        key_validated =
            new_passcode.rangeOfKeysValid(first_key_it, last_key_it);
        */
      }
      if (not key_validated) {
        insertKeyDigits(new_key);
      }
    }
    // else, passcode already valid for new key
    linkKeyDigits(new_key);
  }

  friend std::ostream &operator<<(std::ostream &out, const Passcode &passcode);

private:
  void linkKeyDigits(const Key &key) {
    auto found_iter = digits.begin();
    for (auto digit_it = key.cbegin(); digit_it != --key.cend();) {
      found_iter =
          std::find_if(found_iter, digits.end(), [&](const Valid_Digit_t &vd) {
            return vd.first == *digit_it;
          });
      auto &linked_digits = found_iter->second;
      ++digit_it;
      if (std::find(linked_digits.cbegin(), linked_digits.cend(), *digit_it) ==
          linked_digits.end())
        linked_digits.push_back(*digit_it);
    }
  }
  std::list<Valid_Digit_t> digits;
};
std::ostream &operator<<(std::ostream &out, const Passcode &passcode) {
  for (const auto &valid_digit : passcode.digits)
    out << valid_digit.first;
}

// function prototypes
Keys readKeylog(const char *filename);
void sortAndRemoveDuplicates(Keys &keys);

int main() {
  auto keys =
      readKeylog("../../../solutions/051-100/Problem079/p079_keylog.txt");

  sortAndRemoveDuplicates(keys);

  Passcode passcode(keys.front());

  for (auto key_it = keys.cbegin(); key_it != keys.cend(); ++key_it)
    passcode.validateNewKey(keys.cbegin(), key_it);

  std::cout << "Passcode is " << passcode;
}

Keys readKeylog(const char *filename) {
  std::ifstream file(filename);
  if (file.fail()) {
    std::cerr << "Failed to open the file" << std::endl;
    exit(1);
  }

  Keys keys;
  keys.reserve(50);

  const unsigned LOGIN_COUNT = 50;
  for (unsigned login = 0; login < LOGIN_COUNT; ++login) {
    std::string key_str;
    std::getline(file, key_str);
    keys.emplace_back(Key(key_str));
  }

  return keys;
}

void sortAndRemoveDuplicates(Keys &keys) {
  std::sort(keys.begin(), keys.end());
  auto new_end = std::unique(keys.begin(), keys.end());
  keys.erase(new_end, keys.end());
}

/*
StrNum rearrangePasscode(const std::vector<StrNum>::const_iterator &first_key,
                         const std::vector<StrNum>::const_iterator &last_key,
                         StrNum passcode) {
  auto &invalid_key = *last_key;
  // TODO: implement using linked-list
  return passcode;
}
*/

/* First thoughts
 * 1. This problem requires storing and updating the passcode as we look at each
 * new key. The passcode must be valid for every key in the file. This means
 * that the relative positions of the digits in the key must be found within the
 * passcode. If it is not found, we must update the passcode so that it becomes
 * valid for that particular key.
 * 2. This problem  becomes easier to analyze if we sort the keys and remove any
 * duplicates.
 * 3. If the entire sequence is not found within the passcode, we can just add
 * those digits to the end of the passcode.
 * 4. For every new key that we validate, we are modifying the passcode. In
 * doing so, we must make sure that all previously validated keys will still be
 * valid after this modification.
 * 5. We initialize the passcode with the first key, otherwise it would be
 * initialized with 0 due to StrNum's default ctor. The digit 0 will be added
 * eventually but, for now, we initialize with first key to aid in debugging.
 * 6. When modifying the passcode, there are two options: reorganization or
 * insertion. Reorganization should be attempted first, as the goal is to have
 * the shortest possible passcode and, thus, least amount of insertions.
 * 7. Reorganizing the passcode digits is required when the passcode contains
 * the digits needed for a given key, but in the wrong order. Reorganization
 * fails if the resulting passcode is not valid for all previous keys as well.
 * 8. Reorganizing the passcode digits can be made easier by using a linked list
 * to store the individual digits of the passcode, as well as pointers to
 * proceeding digits that together form part of a validated key.
 * 9. Inserting a digit into the passcode is required when reorganization fails
 * or isn't an option. If other digits in that key are already in the passcode,
 * the insertion point should be such that it will complete the missing key
 * sequence. */
