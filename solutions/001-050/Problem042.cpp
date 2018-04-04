/* Coded triangle numbers
 * The nth term of the sequence of triangle numbers is given
 * by, tn = ½n(n+1); so the first ten triangle numbers are:
 *
 *          1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * By converting each letter in a word to a number corresponding
 * to its alphabetical position and adding these values we form
 * a word value. For example, the word value for SKY is
 * 19 + 11 + 25 = 55 = t10. If the word value is a triangle
 * number then we shall call the word a triangle word.
 *
 * Using words.txt (right click and 'Save Link/Target As...'), a
 * 16K text file containing nearly two-thousand common English
 * words, how many are triangle words? */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<unsigned> getTriangleNumbers();

std::string readNextWord(std::ifstream &file);

unsigned calcWordValue(const std::string &word);

bool foundTriangleWord(unsigned value, std::vector<unsigned> nums);

int main() {
    std::ifstream file;
    file.open("../../../solutions/001-050/Problem042/p042_words.txt");
    if( file.fail() ) {
        std::cerr << "Could not open file. "
                  << "Recheck everything!!!"
                  << std::endl;
        exit(1);
    }

    std::vector<unsigned> triNums = getTriangleNumbers();

    std::string wordStr;
    unsigned wordValue = 0;
    unsigned triWordCount = 0;
    while( !file.eof() ) {
        wordStr = readNextWord(file);
        wordValue = calcWordValue(wordStr);
        if( foundTriangleWord(wordValue,triNums) )
            ++triWordCount;
    }

    std::cout << "result: " << triWordCount << std::endl;
}

bool foundTriangleWord(unsigned value
        ,std::vector<unsigned> nums) {
    auto it = std::find(nums.begin(),nums.end(),value);
    return it != nums.end();
}

unsigned calcWordValue(const std::string &word) {
    unsigned value = 0;
    for( auto i=0u; i<word.size(); ++i )
        value += word[i] - 'A' + 1;
    return value;
}

std::string readNextWord(std::ifstream &file) {
    std::string word;
    char nextChar;

    // read first quote mark
    file.read(&nextChar,1);
    do {
        file.read(&nextChar,1);
        word.push_back(nextChar);
    } while( nextChar!='\"' );
    // remove last quote from word
    word.pop_back();

    // read next char, which can be either
    // a comma or EOF mark
    file.read(&nextChar,1);

    return word;
}

std::vector<unsigned> getTriangleNumbers() {
    std::vector<unsigned> nums;
    for( auto i=1u; i<=20; ++i )
        nums.push_back( i*(i+1)/2 );
    return nums;
}
