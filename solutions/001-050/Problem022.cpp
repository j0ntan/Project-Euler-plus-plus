/* Using names.txt (right click and 'Save Link/Target As...'), a 46K text
 * file containing over five-thousand first names, begin by sorting it
 * into alphabetical order. Then working out the alphabetical value for
 * each name, multiply this value by its alphabetical position in the list
 * to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN,
 * which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the
 * list. So, COLIN would obtain a score of 938 × 53 = 49714.
 *
 * What is the total of all the name scores in the file? */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

std::string readNextName(std::ifstream &file);

short getNameScore(const std::string &name);

int main() {
    std::ifstream file;
    file.open("../../../solutions/001-050/Problem022/p022_names.txt");
    if( file.fail() ) {
        std::cerr << "Error. Could not open file." << std::endl;
        exit(1);
    }

    // store names in vector
    std::vector<std::string> names;
    while( !file.eof() )
        names.push_back( readNextName(file) );
    names.pop_back();   // remove empty string from reaching EOF

    // sort that bad boy
    std::sort( names.begin(),names.end() );

    // calculate ea. name score
    auto size = names.size();
    std::vector<short> nameScores( size,0 );
    for( auto i=0u; i<size; ++i )
        nameScores[i] = getNameScore( names[i] );

    // get total of all name scores
    auto result=0UL;
    for( auto i=0u; i<size; ++i )
        result += (i+1) * nameScores[i];

    std::cout << "result: " << result << std::endl;
}

short getNameScore(const std::string &name) {
    short score = 0;
    for( auto i=0u; i<name.size(); ++i )
        score += name[i] - 'A' + 1;

    return score;
}

std::string readNextName(std::ifstream &file) {
    bool q_mark = false; // flag for double quote mark

    // find opening quotation
    while( q_mark==false && !file.eof() )
        q_mark = static_cast<char>( file.get() ) == '"';

    q_mark = false;
    std::string name;
    while( q_mark==false && !file.eof() ) {
        char readChar = static_cast<char>( file.get() );
        if( readChar == '"' ) q_mark = true;
        else name.push_back( readChar );
    }

    return name;
}