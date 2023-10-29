/**
 * @file zsp01_tests.cpp
 * @brief This file contains all the unit tests for ZSP Tasks functionalities.
 *
 * @author Evgenii Shiliaev
 * @date 29.10.2023
 */

#include "zsp01_functions.h"
#include <cstdio>
#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include <string>

class StdinStreamBuffer : public std::streambuf
{
  public:
    StdinStreamBuffer(const std::string &s) : data(s)
    {
        setg(&data[0], &data[0], &data[0] + data.size());
    }
    int_type underflow()
    {
        return gptr() == egptr() ? traits_type::eof() : traits_type::to_int_type(*gptr());
    }

  private:
    std::string data;
};

void runTestWithInput(const std::string &input, std::string &output)
{
    // Create a temporary file and write the input to it
    FILE *tmp = tmpfile();
    fwrite(input.c_str(), sizeof(char), input.length(), tmp);
    rewind(tmp); // Reset the file pointer to the beginning

    // Redirect stdin to read from the temporary file
    FILE *originalStdin = stdin;
    stdin = tmp;

    testing::internal::CaptureStdout();

    u1_1();

    output = testing::internal::GetCapturedStdout();

    stdin = originalStdin; // Reset stdin
    fclose(tmp);           // Close and delete the temporary file
}

TEST(U1_1Tests, SampleTest)
{
    std::string input = "5 100"; // 5 items at a price of 100 each.
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 100 Kč\tCena s DPH/ks 120 Kč\nPočet kusů: 5\tCena bez DPH "
                                 "500 Kč\tCena s DPH (20 %) 600 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}
TEST(U1_1Tests, TestSingleItem)
{
    std::string input = "1 100";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 100 Kč\tCena s DPH/ks 120 Kč\nPočet kusů: 1\tCena bez DPH "
                                 "100 Kč\tCena s DPH (20 %) 120 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestZeroItem)
{
    std::string input = "0 100";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 100 Kč\tCena s DPH/ks 120 Kč\nPočet kusů: 0\tCena bez DPH "
                                 "0 Kč\tCena s DPH (20 %) 0 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_10_Price_50)
{
    std::string input = "10 50";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 50 Kč\tCena s DPH/ks 60 Kč\nPočet kusů: 10\tCena bez DPH "
                                 "500 Kč\tCena s DPH (20 %) 600 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_2_Price_150)
{
    std::string input = "2 150";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 150 Kč\tCena s DPH/ks 180 Kč\nPočet kusů: 2\tCena bez DPH "
                                 "300 Kč\tCena s DPH (20 %) 360 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_3_Price_200)
{
    std::string input = "3 200";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 200 Kč\tCena s DPH/ks 240 Kč\nPočet kusů: 3\tCena bez DPH "
                                 "600 Kč\tCena s DPH (20 %) 720 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_7_Price_70)
{
    std::string input = "7 70";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 70 Kč\tCena s DPH/ks 84 Kč\nPočet kusů: 7\tCena bez DPH 490 "
                                 "Kč\tCena s DPH (20 %) 588 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_1_Price_500)
{
    std::string input = "1 500";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 500 Kč\tCena s DPH/ks 600 Kč\nPočet kusů: 1\tCena bez DPH "
                                 "500 Kč\tCena s DPH (20 %) 600 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_4_Price_25)
{
    std::string input = "4 25";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 25 Kč\tCena s DPH/ks 30 Kč\nPočet kusů: 4\tCena bez DPH 100 "
                                 "Kč\tCena s DPH (20 %) 120 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_15_Price_10)
{
    std::string input = "15 10";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 10 Kč\tCena s DPH/ks 12 Kč\nPočet kusů: 15\tCena bez DPH "
                                 "150 Kč\tCena s DPH (20 %) 180 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_20_Price_300)
{
    std::string input = "20 300";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 300 Kč\tCena s DPH/ks 360 Kč\nPočet kusů: 20\tCena bez DPH "
                                 "6000 Kč\tCena s DPH (20 %) 7200 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_1_Price_1)
{
    std::string input = "1 1";
    std::string expectedOutput =
        "Účtenka\nCena bez DPH/ks 1 Kč\tCena s DPH/ks 1 Kč\nPočet kusů: 1\tCena bez DPH 1 Kč\tCena s DPH (20 %) 1 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_5_Price_5)
{
    std::string input = "5 5";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 5 Kč\tCena s DPH/ks 6 Kč\nPočet kusů: 5\tCena bez DPH 25 "
                                 "Kč\tCena s DPH (20 %) 30 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_50_Price_25)
{
    std::string input = "50 25";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 25 Kč\tCena s DPH/ks 30 Kč\nPočet kusů: 50\tCena bez DPH "
                                 "1250 Kč\tCena s DPH (20 %) 1500 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_3_Price_7)
{
    std::string input = "3 7";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 7 Kč\tCena s DPH/ks 8 Kč\nPočet kusů: 3\tCena bez DPH 21 "
                                 "Kč\tCena s DPH (20 %) 24 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_17_Price_13)
{
    std::string input = "17 13";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 13 Kč\tCena s DPH/ks 16 Kč\nPočet kusů: 17\tCena bez DPH "
                                 "221 Kč\tCena s DPH (20 %) 272 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_29_Price_19)
{
    std::string input = "29 19";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 19 Kč\tCena s DPH/ks 23 Kč\nPočet kusů: 29\tCena bez DPH "
                                 "551 Kč\tCena s DPH (20 %) 667 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_47_Price_31)
{
    std::string input = "47 31";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 31 Kč\tCena s DPH/ks 37 Kč\nPočet kusů: 47\tCena bez DPH "
                                 "1457 Kč\tCena s DPH (20 %) 1739 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_59_Price_41)
{
    std::string input = "59 41";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 41 Kč\tCena s DPH/ks 49 Kč\nPočet kusů: 59\tCena bez DPH "
                                 "2419 Kč\tCena s DPH (20 %) 2891 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_67_Price_23)
{
    std::string input = "67 23";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 23 Kč\tCena s DPH/ks 28 Kč\nPočet kusů: 67\tCena bez DPH "
                                 "1541 Kč\tCena s DPH (20 %) 1876 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_79_Price_37)
{
    std::string input = "79 37";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 37 Kč\tCena s DPH/ks 44 Kč\nPočet kusů: 79\tCena bez DPH "
                                 "2923 Kč\tCena s DPH (20 %) 3476 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_89_Price_53)
{
    std::string input = "89 53";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 53 Kč\tCena s DPH/ks 64 Kč\nPočet kusů: 89\tCena bez DPH "
                                 "4717 Kč\tCena s DPH (20 %) 5696 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_97_Price_29)
{
    std::string input = "97 29";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 29 Kč\tCena s DPH/ks 35 Kč\nPočet kusů: 97\tCena bez DPH "
                                 "2813 Kč\tCena s DPH (20 %) 3395 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

TEST(U1_1Tests, TestItem_101_Price_43)
{
    std::string input = "101 43";
    std::string expectedOutput = "Účtenka\nCena bez DPH/ks 43 Kč\tCena s DPH/ks 52 Kč\nPočet kusů: 101\tCena bez DPH "
                                 "4343 Kč\tCena s DPH (20 %) 5252 Kč\n";
    std::string actualOutput;
    runTestWithInput(input, actualOutput);
    ASSERT_EQ(expectedOutput, actualOutput);
}

// ... Add more test cases as necessary ...

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/** End of zsp01_tests.cpp */