/**
 * @file tests.cpp
 * @brief This file contains all the unit tests for ZSP Tasks functionalities.
 *
 * This file is NOT part of the submitted solution.
 * It's meant only for debugging and testing purposes.
 *
 * @see https://github.com/Jekwwer/ZSP-Project01-2023
 *
 * @author Evgenii Shiliaev
 * @date October 29, 2023 (Creation)
 *       November 13, 2023 (Comment enhancements)
 */

#include "functions.h"
#include <cstdio>
#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include <string>

/**
 * @class StdinStreamBuffer
 * @brief Custom stream buffer for simulating standard input in unit tests.
 *
 * @details This class is derived from std::streambuf and is used to redirect the standard input
 *          stream (stdin) for unit testing purposes. It allows for the simulation of user input
 *          by providing a string buffer from which input is read instead of the standard console input.
 *          This is particularly useful for testing functions that require user input without
 *          manually entering data during tests.
 *
 *          The class overrides the underflow method to provide characters from the given string.
 *          It is typically used in conjunction with a testing framework to automate input for functions
 *          that read from stdin.
 *
 *          Example Usage:
 *          @code
 *          StdinStreamBuffer testBuffer("test input");
 *          std::cin.rdbuf(&testBuffer);
 *          // Now any input operation on std::cin will read from "test input" instead
 *          @endcode
 *
 * @note This class is designed specifically for testing and should not be used in production code.
 */
class StdinStreamBuffer : public std::streambuf
{
  public:
    /**
     * @brief Constructs a StdinStreamBuffer with the given input data.
     *
     * @details Initializes the stream buffer using the provided string. The string 's' is used as
     *          the source of data for the buffer. This constructor prepares the buffer to read
     *          from the provided string instead of the standard input.
     *
     * @param s The string that will be used as the source of data for the buffer.
     *
     * @note The input string 's' should contain the data that is expected to be read as input
     *       during the execution of the test cases.
     */
    StdinStreamBuffer(const std::string &s) : data(s)
    {
        setg(&data[0], &data[0], &data[0] + data.size());
    }
    /**
     * @brief Retrieves the next character from the input buffer without changing the buffer state.
     *
     * @details This method is called when reading from the buffer and the current get pointer (gptr)
     *          equals the end get pointer (egptr), indicating that the buffer is currently empty.
     *          It returns the next character from the input sequence or EOF if the end of the sequence is reached.
     *          This method overrides the standard underflow behavior of std::streambuf to read from
     *          the custom input buffer provided during construction.
     *
     * @return The next character as an int_type value, or traits_type::eof() if the end of the buffer is reached.
     *
     * @note This method plays a crucial role in redirecting input from the standard input stream
     *       to the buffer provided in the class constructor.
     */
    int_type underflow()
    {
        return gptr() == egptr() ? traits_type::eof() : traits_type::to_int_type(*gptr());
    }

  private:
    std::string data;
};

/**
 * @brief Executes a test for a specified function using simulated input and captures the output.
 *
 * @details This function is used for testing other functions that require standard input. It simulates
 *          the input by redirecting the standard input stream to a temporary file containing the provided
 *          input string. After executing the function, it captures and returns the output, allowing
 *          for automated testing of functions that read from standard input and write to standard output.
 *
 *          The function handles the setup and teardown of the simulation environment, including file
 *          creation, stream redirection, and output capture.
 *
 * @param input The string to be used as simulated input for the test.
 * @param output A reference to a string where the function's output will be stored.
 * @param functionToTest Pointer to the function that will be tested.
 *
 * @note This function is specifically designed for unit testing and should not be used in production code.
 *
 * @code
 * std::string input = "5 100"; // Simulated input
 * std::string actualOutput;
 * runTestWithInputForFunction(input, actualOutput, u1_1); // Testing u1_1 function
 * ASSERT_EQ("Expected output", actualOutput); // Asserting the expected output
 * @endcode
 *
 * @warning Ensure that the provided function pointer is valid and the input string correctly simulates
 *          the expected user input for the function being tested.
 */
void runTestWithInputForFunction(const std::string &input, std::string &output, void (*functionToTest)())
{
    // Create a temporary file and write the input to it
    FILE *tmp = tmpfile();
    fwrite(input.c_str(), sizeof(char), input.length(), tmp);
    rewind(tmp); // Reset the file pointer to the beginning

    // Redirect stdin to read from the temporary file
    FILE *originalStdin = stdin;
    stdin = tmp;

    testing::internal::CaptureStdout();

    functionToTest(); // Call the provided function

    output = testing::internal::GetCapturedStdout();

    stdin = originalStdin; // Reset stdin
    fclose(tmp);           // Close and delete the temporary file
}

// Tests for u1_1
/**
 * @brief Tests VAT calculation for a sample scenario.
 */
TEST(U1_1Tests, SampleTest)
{
    std::string input = "5 100"; // 5 items at a price of 100 each.
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 100 Kč\tCena s DPH/ks 120 Kč\nPočet kusů: 5\tCena bez DPH "
                                 "500 Kč\tCena s DPH (20 %) 600 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Tests VAT calculation for a single item.
 */
TEST(U1_1Tests, TestSingleItem)
{
    std::string input = "1 100";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 100 Kč\tCena s DPH/ks 120 Kč\nPočet kusů: 1\tCena bez DPH "
                                 "100 Kč\tCena s DPH (20 %) 120 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Tests VAT calculation with zero items.
 */
TEST(U1_1Tests, TestZeroItem)
{
    std::string input = "0 100";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 100 Kč\tCena s DPH/ks 120 Kč\nPočet kusů: 0\tCena bez DPH "
                                 "0 Kč\tCena s DPH (20 %) 0 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 10 items at 50 each.
 */
TEST(U1_1Tests, TestItem_10_Price_50)
{
    std::string input = "10 50";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 50 Kč\tCena s DPH/ks 60 Kč\nPočet kusů: 10\tCena bez DPH "
                                 "500 Kč\tCena s DPH (20 %) 600 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 2 items at 150 each.
 */
TEST(U1_1Tests, TestItem_2_Price_150)
{
    std::string input = "2 150";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 150 Kč\tCena s DPH/ks 180 Kč\nPočet kusů: 2\tCena bez DPH "
                                 "300 Kč\tCena s DPH (20 %) 360 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 3 items at 200 each.
 */
TEST(U1_1Tests, TestItem_3_Price_200)
{
    std::string input = "3 200";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 200 Kč\tCena s DPH/ks 240 Kč\nPočet kusů: 3\tCena bez DPH "
                                 "600 Kč\tCena s DPH (20 %) 720 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 7 items at 70 each.
 */
TEST(U1_1Tests, TestItem_7_Price_70)
{
    std::string input = "7 70";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 70 Kč\tCena s DPH/ks 84 Kč\nPočet kusů: 7\tCena bez DPH 490 "
                                 "Kč\tCena s DPH (20 %) 588 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 1 item at 500.
 */
TEST(U1_1Tests, TestItem_1_Price_500)
{
    std::string input = "1 500";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 500 Kč\tCena s DPH/ks 600 Kč\nPočet kusů: 1\tCena bez DPH "
                                 "500 Kč\tCena s DPH (20 %) 600 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 4 items at 25 each.
 */
TEST(U1_1Tests, TestItem_4_Price_25)
{
    std::string input = "4 25";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 25 Kč\tCena s DPH/ks 30 Kč\nPočet kusů: 4\tCena bez DPH 100 "
                                 "Kč\tCena s DPH (20 %) 120 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 15 items at 10 each.
 */
TEST(U1_1Tests, TestItem_15_Price_10)
{
    std::string input = "15 10";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 10 Kč\tCena s DPH/ks 12 Kč\nPočet kusů: 15\tCena bez DPH "
                                 "150 Kč\tCena s DPH (20 %) 180 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 20 items at 300 each.
 */
TEST(U1_1Tests, TestItem_20_Price_300)
{
    std::string input = "20 300";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 300 Kč\tCena s DPH/ks 360 Kč\nPočet kusů: 20\tCena bez DPH "
                                 "6000 Kč\tCena s DPH (20 %) 7200 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 1 item at 1.
 */
TEST(U1_1Tests, TestItem_1_Price_1)
{
    std::string input = "1 1";
    std::string expectedOutput =
        "Účtenka\nCena bez DPH/ks 1 Kč\tCena s DPH/ks 1 Kč\nPočet kusů: 1\tCena bez DPH 1 Kč\tCena s DPH (20 %) 1 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 5 items at 5 each.
 */
TEST(U1_1Tests, TestItem_5_Price_5)
{
    std::string input = "5 5";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 5 Kč\tCena s DPH/ks 6 Kč\nPočet kusů: 5\tCena bez DPH 25 "
                                 "Kč\tCena s DPH (20 %) 30 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 50 items at 25 each.
 */
TEST(U1_1Tests, TestItem_50_Price_25)
{
    std::string input = "50 25";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 25 Kč\tCena s DPH/ks 30 Kč\nPočet kusů: 50\tCena bez DPH "
                                 "1250 Kč\tCena s DPH (20 %) 1500 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 3 items at 7 each.
 */
TEST(U1_1Tests, TestItem_3_Price_7)
{
    std::string input = "3 7";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 7 Kč\tCena s DPH/ks 8 Kč\nPočet kusů: 3\tCena bez DPH 21 "
                                 "Kč\tCena s DPH (20 %) 24 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 17 items at 13 each.
 */
TEST(U1_1Tests, TestItem_17_Price_13)
{
    std::string input = "17 13";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 13 Kč\tCena s DPH/ks 16 Kč\nPočet kusů: 17\tCena bez DPH "
                                 "221 Kč\tCena s DPH (20 %) 272 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 29 items at 19 each.
 */
TEST(U1_1Tests, TestItem_29_Price_19)
{
    std::string input = "29 19";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 19 Kč\tCena s DPH/ks 23 Kč\nPočet kusů: 29\tCena bez DPH "
                                 "551 Kč\tCena s DPH (20 %) 667 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 47 items at 31 each.
 */
TEST(U1_1Tests, TestItem_47_Price_31)
{
    std::string input = "47 31";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 31 Kč\tCena s DPH/ks 37 Kč\nPočet kusů: 47\tCena bez DPH "
                                 "1457 Kč\tCena s DPH (20 %) 1739 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 59 items at 41 each.
 */
TEST(U1_1Tests, TestItem_59_Price_41)
{
    std::string input = "59 41";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 41 Kč\tCena s DPH/ks 49 Kč\nPočet kusů: 59\tCena bez DPH "
                                 "2419 Kč\tCena s DPH (20 %) 2891 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 67 items at 23 each.
 */
TEST(U1_1Tests, TestItem_67_Price_23)
{
    std::string input = "67 23";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 23 Kč\tCena s DPH/ks 28 Kč\nPočet kusů: 67\tCena bez DPH "
                                 "1541 Kč\tCena s DPH (20 %) 1876 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 79 items at 37 each.
 */
TEST(U1_1Tests, TestItem_79_Price_37)
{
    std::string input = "79 37";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 37 Kč\tCena s DPH/ks 44 Kč\nPočet kusů: 79\tCena bez DPH "
                                 "2923 Kč\tCena s DPH (20 %) 3476 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 89 items at 53 each.
 */
TEST(U1_1Tests, TestItem_89_Price_53)
{
    std::string input = "89 53";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 53 Kč\tCena s DPH/ks 64 Kč\nPočet kusů: 89\tCena bez DPH "
                                 "4717 Kč\tCena s DPH (20 %) 5696 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 97 items at 29 each.
 */
TEST(U1_1Tests, TestItem_97_Price_29)
{
    std::string input = "97 29";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 29 Kč\tCena s DPH/ks 35 Kč\nPočet kusů: 97\tCena bez DPH "
                                 "2813 Kč\tCena s DPH (20 %) 3395 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test VAT calculation for 101 items at 43 each.
 */
TEST(U1_1Tests, TestItem_101_Price_43)
{
    std::string input = "101 43";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 43 Kč\tCena s DPH/ks 52 Kč\nPočet kusů: 101\tCena bez DPH "
                                 "4343 Kč\tCena s DPH (20 %) 5252 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_1);
    ASSERT_EQ(expectedOutput, actualOutput);
}

// Tests for u1_2
/**
 * @brief Test processing student grades for perfect scores.
 */
TEST(U1_2Tests, TestPerfectScores)
{
    std::string input = "1 1 1 1 1";
    std::string expectedOutput =
        "Známky: 1\t1\t1\t1\t1\n1.00\nProspěl s vyznamenáním: 1:Ano\nProspěl: 1:Ano\nNeprospěl: 0:Ne\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_2);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test processing student grades with scores for distinction.
 */
TEST(U1_2Tests, TestScoresDistinction)
{
    std::string input = "1 2 1 2 1";
    std::string expectedOutput =
        "Známky: 1\t2\t1\t2\t1\n1.40\nProspěl s vyznamenáním: 1:Ano\nProspěl: 1:Ano\nNeprospěl: 0:Ne\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_2);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test processing student grades with failing scores.
 */
TEST(U1_2Tests, TestFailingScores)
{
    std::string input = "5 5 5 5 5";
    std::string expectedOutput =
        "Známky: 5\t5\t5\t5\t5\n5.00\nProspěl s vyznamenáním: 0:Ne\nProspěl: 0:Ne\nNeprospěl: 1:Ano\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_2);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test processing student grades that almost pass with distinction.
 */
TEST(U1_2Tests, TestPassScores01)
{
    std::string input = "1 2 2 2 2";
    std::string expectedOutput =
        "Známky: 1\t2\t2\t2\t2\n1.80\nProspěl s vyznamenáním: 0:Ne\nProspěl: 1:Ano\nNeprospěl: 0:Ne\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_2);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test processing student grades that almost pass.
 */
TEST(U1_2Tests, TestPassScores02)
{
    std::string input = "3 4 4 4 4";
    std::string expectedOutput =
        "Známky: 3\t4\t4\t4\t4\n3.80\nProspěl s vyznamenáním: 0:Ne\nProspěl: 1:Ano\nNeprospěl: 0:Ne\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_2);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test processing student grades that are on the border of passing.
 */
TEST(U1_2Tests, JustPassed)
{
    std::string input = "4 4 4 4 4";
    std::string expectedOutput =
        "Známky: 4\t4\t4\t4\t4\n4.00\nProspěl s vyznamenáním: 0:Ne\nProspěl: 1:Ano\nNeprospěl: 0:Ne\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_2);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test processing student grades that are on the border of failing.
 */
TEST(U1_2Tests, JustFailed)
{
    std::string input = "4 4 4 4 5";
    std::string expectedOutput =
        "Známky: 4\t4\t4\t4\t5\n4.20\nProspěl s vyznamenáním: 0:Ne\nProspěl: 0:Ne\nNeprospěl: 1:Ano\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_2);
    ASSERT_EQ(expectedOutput, actualOutput);
}

// Tests for u1_3
/**
 * @brief Test currency conversion from GBP to CZK.
 */
TEST(U1_3Tests, TestCurrencyExchangeGBP)
{
    std::string input = "GBP 24.9 5\n";
    std::string expectedOutput = "1 GBP = 24.9 Kč\nNákup: 5 GBP\nCelkem: 5 x 24.9 = 124.5 Kč Zaokrouhleno: 125 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test currency conversion from EUR to CZK.
 */
TEST(U1_3Tests, TestCurrencyExchangeEUR)
{
    std::string input = "EUR 26.3 3\n";
    std::string expectedOutput = "1 EUR = 26.3 Kč\nNákup: 3 EUR\nCelkem: 3 x 26.3 = 78.9 Kč Zaokrouhleno: 79 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test currency conversion from USD to CZK.
 */
TEST(U1_3Tests, TestCurrencyExchangeUSD)
{
    std::string input = "USD 21.8 7\n";
    std::string expectedOutput = "1 USD = 21.8 Kč\nNákup: 7 USD\nCelkem: 7 x 21.8 = 152.6 Kč Zaokrouhleno: 153 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test currency conversion with rounding down scenario.
 */
TEST(U1_3Tests, TestCurrencyExchangeRoundDown1)
{
    std::string input = "GBP 24.1 4\n";
    std::string expectedOutput = "1 GBP = 24.1 Kč\nNákup: 4 GBP\nCelkem: 4 x 24.1 = 96.4 Kč Zaokrouhleno: 96 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test another currency conversion with rounding down scenario.
 */
TEST(U1_3Tests, TestCurrencyExchangeRoundDown2)
{
    std::string input = "EUR 26.2 2\n";
    std::string expectedOutput = "1 EUR = 26.2 Kč\nNákup: 2 EUR\nCelkem: 2 x 26.2 = 52.4 Kč Zaokrouhleno: 52 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test currency conversion with rounding down for a third scenario.
 */
TEST(U1_3Tests, TestCurrencyExchangeRoundDown3)
{
    std::string input = "USD 21.4 3\n";
    std::string expectedOutput = "1 USD = 21.4 Kč\nNákup: 3 USD\nCelkem: 3 x 21.4 = 64.2 Kč Zaokrouhleno: 64 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test currency conversion with a zero amount.
 */
TEST(U1_3Tests, TestCurrencyExchangeWithZeroAmount)
{
    std::string input = "JPY 0.2 0\n";
    std::string expectedOutput = "1 JPY = 0.2 Kč\nNákup: 0 JPY\nCelkem: 0 x 0.2 = 0.0 Kč Zaokrouhleno: 0 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

/**
 * @brief Test currency conversion with a zero currency rate.
 */
TEST(U1_3Tests, TestZeroCurrencyRate)
{
    std::string input = "JPY 0 5\n";
    std::string expectedOutput = "1 JPY = 0.0 Kč\nNákup: 5 JPY\nCelkem: 5 x 0.0 = 0.0 Kč Zaokrouhleno: 0 Kč\n";
    std::string actualOutput;
    runTestWithInputForFunction(input, actualOutput, u1_3);
    ASSERT_EQ(expectedOutput, actualOutput);
}

// ... Add more test cases as necessary ...

/**
 * @brief Main function for running all unit tests.
 *
 * @details Initializes the Google Test framework and runs all the test cases defined in this file.
 *          This function is the entry point for running automated tests on various functions implemented
 *          in the project, ensuring they behave as expected.
 *
 * @note This function should only be used for testing purposes and not be part of the production code.
 *
 * @return Returns the status of the test execution. A non-zero return value indicates that some tests failed.
 */
int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

/** End of tests.cpp */