/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <cmath>
#include <iostream>
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;

/* The divisorSum function takes one argument `n` and calculates the
 * sum of proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division using the modulus operator %
 *
 * Note: the C++ long type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* The isPerfect function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* The findPerfects function takes one argument `stop` and performs
 * an exhaustive search for perfect numbers over the range 1 to `stop`.
 * Each perfect number found is printed to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
//wanna check up till sqrt(n)
long smarterSum(long n) {
    if (n <= 1) return 0;

    long total = 0;

    for (long divisor = 1; divisor <= sqrt(n); divisor++) {
        if (n % divisor == 0) {

            long partner = n / divisor;

            total += divisor;

            if (partner != n && partner != divisor) {
                total += partner;
            }
        }
    }

    return total;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void findPerfectsSmarter(long stop) {

    if (stop < 6)
    {
        std::cout << "No perfect number smaller than 6.";
        return;
    }

    for (long num = 6; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */

bool isPrime (long n)
{
    if (n < 2){
        return false;
    }

    for (size_t i = 2; i <= sqrt(n); ++i){
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

long findNthPerfectEuclid(long n) {
    long count = 0;
    long p = 2;
    long perfect = 0;

    while (count < n) {
        long mersenne = pow(2, p) - 1;

        if (isPrime(mersenne)) {
            perfect = pow(2, p - 1) * mersenne;
            ++count;
        }

        ++p;
    }

    return perfect;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(1000, findPerfects(1000));
}


// TODO: add your student test cases here

STUDENT_TEST("Test smarterSum with different inputs") {
    EXPECT_EQUAL(smarterSum(1), 0);
    EXPECT_EQUAL(smarterSum(6), 6);
    EXPECT_EQUAL(smarterSum(12), 16);
    EXPECT_EQUAL(smarterSum(28), 28);
    EXPECT_EQUAL(smarterSum(36), 55);
}

STUDENT_TEST("Test isPerfectSmarter") {
    EXPECT(isPerfectSmarter(6));
    EXPECT(isPerfectSmarter(28));
    EXPECT(isPerfectSmarter(496));

    EXPECT(!isPerfectSmarter(0));
    EXPECT(!isPerfectSmarter(1));
    EXPECT(!isPerfectSmarter(12));
    EXPECT(!isPerfectSmarter(97));
}

STUDENT_TEST("Test findPerfectsSmarter") {
    findPerfectsSmarter(7);
    findPerfectsSmarter(30);
    findPerfectsSmarter(500);
}

STUDENT_TEST("Test isPrime") {
    EXPECT(isPrime(2));
    EXPECT(isPrime(3));
    EXPECT(isPrime(7));
    EXPECT(isPrime(31));
    EXPECT(isPrime(97));

    EXPECT(!isPrime(0));
    EXPECT(!isPrime(1));
    EXPECT(!isPrime(4));
    EXPECT(!isPrime(9));
    EXPECT(!isPrime(49));
}

STUDENT_TEST("Test findNthPerfectEuclid") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
}

/*
 * Below is a suggestion of how to use a loop to set the input sizes
 * for a sequence of time trials.
 *
 *
STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {

    int smallest = 1000, largest = 8000;

    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfects(size));
    }
}

*/
