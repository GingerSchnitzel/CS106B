/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <cctype>
#include <fstream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;

/* This function is intended to return a string which
 * includes only the letter characters from the original
 * (all non-letter characters are excluded)
 *
 * WARNING: The provided code is buggy!
 *
 * Use test cases to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */

//Lookup string table
const string groups[] = {
    "AEIOUHWY",  // 0
    "BFPV",      // 1
    "CGJKQSXZ",  // 2
    "DT",        // 3
    "L",         // 4
    "MN",        // 5
    "R"          // 6
};

string lettersOnly(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

string encodeLetters(const string& s) {
    string encoded;

    for (char c : s) {
        char letter = toupper(c);

        for (size_t i = 0; i < 7; ++i) {
            if (groups[i].find(letter) != string::npos) {
                char digit = static_cast<char>(i + '0');
                encoded.push_back(digit);
                break;
            }
        }
    }

    return encoded;
}

string removeAdjacentDuplicates(const string& s)
{
    string result;

    for (size_t i = 0; i < s.length(); ++i)
    {
        if (i == 0 || s[i] != s[i - 1])
        {
            result.push_back(s[i]);
        }
    }

    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string soundex(string s) {
    // Step 1: Keep only letters.
    string normalized = lettersOnly(s);

    // Step 2: Encode each letter as a digit.
    string encoded = encodeLetters(normalized);

    // Step 3: Remove adjacent duplicate digits.
    string result = removeAdjacentDuplicates(encoded);

    // Step 4: Restore the original first letter in uppercase.
    char firstChar = toupper(normalized[0]);
    result[0] = firstChar;

    // Step 5: Remove zeros, preserving the first letter.
    string noZeros;
    noZeros += firstChar;

    for (size_t i = 1; i < result.length(); i++) {
        if (result[i] != '0') {
            noZeros += result[i];
        }
    }

    // Step 6: Truncate to four characters or pad with zeros.
    noZeros = noZeros.substr(0, 4);

    while (noZeros.length() < 4) {
        noZeros += '0';
    }

    return noZeros;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // This provided code opens the specified file
    // and reads the lines into a vector of strings
    ifstream in;
    Vector<string> allNames;

    if (openFile(in, filepath)) {
        allNames = readLines(in);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl;

    // The names read from file are now stored in Vector allNames

    /* TODO: Fill in the remainder of this function. */
}


/* * * * * * Test Cases * * * * * */

STUDENT_TEST("lettersOnly handles first character correctly") {
    EXPECT_EQUAL(lettersOnly("9Planet"), "Planet");
    EXPECT_EQUAL(lettersOnly("!Hello"), "Hello");
    EXPECT_EQUAL(lettersOnly("123"), "");
    EXPECT_EQUAL(encodeLetters("Curie"), "20600");
    EXPECT_EQUAL(encodeLetters("JACKSON"), "2022205");
    EXPECT_EQUAL(encodeLetters("bfpv"), "1111");

}

STUDENT_TEST("Remove adjacent duplicate digits") {
    EXPECT_EQUAL(removeAdjacentDuplicates("222025"), "2025");
    EXPECT_EQUAL(removeAdjacentDuplicates("112233"), "123");
    EXPECT_EQUAL(removeAdjacentDuplicates("10101"), "10101");
    EXPECT_EQUAL(removeAdjacentDuplicates("5555"), "5");
    EXPECT_EQUAL(removeAdjacentDuplicates("123456"), "123456");
    EXPECT_EQUAL(removeAdjacentDuplicates(""), "");
}

PROVIDED_TEST("Test exclude of punctuation, digits, and spaces") {
    string s = "O'Hara";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here


