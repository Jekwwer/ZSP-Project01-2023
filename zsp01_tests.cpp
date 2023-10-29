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

// ... Add more test cases as necessary ...

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/** End of zsp01_tests.cpp */