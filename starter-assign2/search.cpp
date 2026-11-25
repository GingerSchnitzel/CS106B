// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include <algorithm>
#include <cctype>
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;


// Removes all non-alphanumeric characters and converts
// all remaining characters to lowercase.
string cleanToken(string s) {
    s.erase(
        remove_if(s.begin(), s.end(), [](unsigned char c) {
            return !isalnum(c);
        }),
        s.end()
        );

    for (char& c : s) {
        c = tolower(static_cast<unsigned char>(c));
    }

    return s;
}

/*
 * Splits the input text into individual words, cleans each word using
 * cleanToken(), and stores the resulting non-empty tokens in a Set.
 * Duplicate tokens are automatically eliminated by the Set.
 */
Set<string> gatherTokens(string text) {
    Set<string> tokens;
    Vector<string> split = stringSplit(text, " ");

    for (string word : split) {
        string cleaned = cleanToken(word);

        if (!cleaned.empty()) {
            tokens.add(cleaned);
        }
    }

    return tokens;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
int buildIndex(string dbfile, Map<string, Set<string>>& index) {
    return 0;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query) {
    Set<string> result;
    // TODO: your code here
    return result;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string dbfile) {
    // TODO: your code here
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings of letters and digits") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS106B"), "cs106b");
}

PROVIDED_TEST("cleanToken on strings containing punctuation") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
    EXPECT_EQUAL(cleanToken("they're"), "theyre");
}

PROVIDED_TEST("cleanToken on string of only punctuation") {
    EXPECT_EQUAL(cleanToken("#$^@@.;"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 6 unique tokens, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 6);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 12 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 12);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here
STUDENT_TEST("cleanToken removes punctuation") {
    EXPECT_EQUAL(cleanToken("Hello, World!"), "helloworld");
    EXPECT_EQUAL(cleanToken("Don't stop!"), "dontstop");
    EXPECT_EQUAL(cleanToken("a-b_c"), "abc");
}

STUDENT_TEST("cleanToken converts uppercase to lowercase") {
    EXPECT_EQUAL(cleanToken("HELLO"), "hello");
    EXPECT_EQUAL(cleanToken("HeLLo WoRLd"), "helloworld");
}

STUDENT_TEST("cleanToken handles numbers") {
    EXPECT_EQUAL(cleanToken("CS106B"), "cs106b");
    EXPECT_EQUAL(cleanToken("123-456"), "123456");
}

STUDENT_TEST("cleanToken handles empty and unusual input") {
    EXPECT_EQUAL(cleanToken(""), "");
    EXPECT_EQUAL(cleanToken("!!!"), "");
    EXPECT_EQUAL(cleanToken("   "), "");
    EXPECT_EQUAL(cleanToken("A"), "a");
}

STUDENT_TEST("gatherTokens basic tests") {
    EXPECT_EQUAL(gatherTokens("Hello World"), {"hello", "world"});
    EXPECT_EQUAL(gatherTokens("Hello, World!"), {"hello", "world"});
    EXPECT_EQUAL(gatherTokens("Hello Hello"), {"hello"});
}

STUDENT_TEST("gatherTokens handles punctuation and numbers") {
    EXPECT_EQUAL(gatherTokens("CS106B is fun!"), {"cs106b", "is", "fun"});
    EXPECT_EQUAL(gatherTokens("One, two, three."), {"one", "two", "three"});
}

STUDENT_TEST("gatherTokens handles empty input") {
    EXPECT_EQUAL(gatherTokens(""), {});
    EXPECT_EQUAL(gatherTokens("!!!"), {});
}