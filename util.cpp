//
// Created by Baron Wang on 9/21/25.
//

#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;

bool isLetter(char input) {
    if (isalnum(input)) {
        return true;
    } else {
        return false;
    }
}

string convToLower(string src)
{
    for (size_t i = 0; i < src.size(); i++) {
        src[i] = tolower(src[i]);
    }
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWords)
{
    rawWords = convToLower(rawWords);

    std::set<std::string> result;
    std::string current;

    for (size_t i = 0; i < rawWords.size(); i++) {
        char c = rawWords[i];

        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            current += c;
        } else {
            if (current.size() >= 2) {
                result.insert(current);
            }
            current.clear();
        }
    }

    if (current.size() >= 2) {
        result.insert(current);
    }

    return result;
}





/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(),
        std::find_if(s.begin(),
             s.end(),
             std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
        std::find_if(s.rbegin(),
             s.rend(),
             std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
        s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}


