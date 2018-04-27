/* XOR decryption
 * Each character on a computer is assigned a unique code and the preferred
 * standard is ASCII (American Standard Code for Information Interchange). For
 * example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.
 *
 * A modern encryption method is to take a text file, convert the bytes to
 * ASCII, then XOR each byte with a given value, taken from a secret key. The
 * advantage with the XOR function is that using the same encryption key on the
 * cipher text, restores the plain text; for example, 65 XOR 42 = 107, then 107
 * XOR 42 = 65.
 *
 * For unbreakable encryption, the key is the same length as the plain text
 * message, and the key is made up of random bytes. The user would keep the
 * encrypted message and the encryption key in different locations, and without
 * both "halves", it is impossible to decrypt the message.
 *
 * Unfortunately, this method is impractical for most users, so the modified
 * method is to use a password as a key. If the password is shorter than the
 * message, which is likely, the key is repeated cyclically throughout the
 * message. The balance for this method is using a sufficiently long password
 * key for security, but short enough to be memorable.
 *
 * Your task has been made easy, as the encryption key consists of three lower
 * case characters. Using cipher.txt (right click and 'Save Link/Target As...'),
 * a file containing the encrypted ASCII codes, and the knowledge that the plain
 * text must contain common English words, decrypt the message and find the sum
 * of the ASCII values in the original text. */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// function prototypes
void readEncodedFile(const std::string &filename, std::vector<char> &storage);
char readNextByte(std::ifstream &file);
std::string decipher(const std::vector<char> &ciphertext,
                     const std::vector<char> &password);
bool search(const std::string &plaintext);
std::vector<char> nextPasswordPermutation(std::vector<char> &letters);
unsigned addASCIIvalues(const std::string &text);

int main() {
  // get vector of letters
  std::vector<char> letters(26, 'a');
  std::iota(letters.begin(), letters.end(), 'a');

  std::vector<char> ciphertext;
  ciphertext.reserve(3000);
  readEncodedFile("../../../solutions/051-100/Problem059/p059_cipher.txt",
                  ciphertext);

  // attempt to decode with each password permutation
  std::vector<char> password(letters.begin(), letters.begin() + 3);
  auto correct_password = password;
  std::string plaintext;
  bool found_common_words = false;
  do {
    plaintext = decipher(ciphertext, password);
    found_common_words = search(plaintext);
    if (found_common_words)
      correct_password = password;
    password = nextPasswordPermutation(letters);
  } while (not found_common_words and
           password != std::vector<char>{'a', 'b', 'c'});

  std::cout << "Found a match." << std::endl;
  std::cout << "The correct password is \"" << correct_password[0]
            << correct_password[1] << correct_password[2] << '"' << std::endl;
  std::cout << "The sum of ASCII values in the deciphered text is "
            << addASCIIvalues(plaintext);
}

char readNextByte(std::ifstream &file) {
  std::string digits;
  std::getline(file, digits, ',');
  if (digits.back() == '\n') {
    digits.pop_back();
    file.unget();
  }
  return static_cast<char>(std::stoi(digits));
}

void readEncodedFile(const std::string &filename, std::vector<char> &storage) {
  std::ifstream file{filename};
  if (file.fail()) {
    std::cerr << "Failed to open the file" << std::endl;
    exit(1);
  }

  while (file.peek() != static_cast<int>('\n'))
    storage.push_back(readNextByte(file));
}

std::string decipher(const std::vector<char> &ciphertext,
                     const std::vector<char> &password) {
  std::string plaintext;
  plaintext.reserve(ciphertext.size());

  for (unsigned i = 0; i < ciphertext.size(); i += password.size())
    for (unsigned j = 0; j < password.size() and (i + j) < ciphertext.size();
         ++j)
      plaintext.push_back(ciphertext[i + j] ^ password[j]);

  return plaintext;
}

bool search(const std::string &plaintext) {
  const bool found_the = plaintext.find("the") != std::string::npos;
  const bool found_be = plaintext.find("be") != std::string::npos;
  const bool found_to = plaintext.find("to") != std::string::npos;
  const bool found_of = plaintext.find("of") != std::string::npos;
  const bool found_and = plaintext.find("and") != std::string::npos;
  const bool found_in = plaintext.find("in") != std::string::npos;
  return found_the and found_be and found_to and found_of and found_and and
         found_in;
}

std::vector<char> nextPasswordPermutation(std::vector<char> &letters) {
  std::reverse(letters.begin() + 3, letters.end());
  std::next_permutation(letters.begin(), letters.end());
  return std::vector<char>(letters.begin(), letters.begin() + 3);
}

unsigned addASCIIvalues(const std::string &text) {
  unsigned sum = 0;
  for (auto letter : text)
    sum += static_cast<unsigned>(letter);
  return sum;
}

/* First thoughts
 * 1. As a first attempt, we can try a brute force approach. This involves
 * trying different permutations of 3-character passwords. We can decrypt with
 * each permutation and search for a common English word. According to a ranking
 * based on the OEC (*), the most common English word is "the", thus our search
 * will look for this word.
 * (*) https://en.wikipedia.org/wiki/Most_common_words_in_English
 * 2. Finding the sum of the ASCII values is straight-forward, but due to the
 * nature of cryptography it seems likely that the encoded message will affect
 * the final answer to this problem somehow.
 * 3. After adding the next three common words in the search, there were several
 * matches found that resulted in partially decoded words. In order to find the
 * final, correct, matching password, we added two more common words to look for
 * in the search.
 * 4. Having a search of 6 common words resulted in a correct match that fully
 * deciphered the text. One improvement that can be made is to convert the
 * plaintext to lowercase characters before searching for the common words. This
 * prevents a missing a word match due to capitalization. */
