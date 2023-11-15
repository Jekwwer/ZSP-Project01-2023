/**
 * @file functions.h
 * @brief Function Declarations for ZSP VŠPJ 1st Homework Assignment.
 * @details This header file contains the declarations of functions used in the 1st homework
 *          assignment for the ZSP VŠPJ (Fundamentals of Structural Programming) course. It includes
 *          function prototypes for calculating prices with VAT (u1_1), processing student grades (u1_2),
 *          and performing currency conversions (u1_3). These functions are implemented in the
 *          corresponding `functions.cpp` file.
 *
 *          The primary purpose of this file is to provide clear, structured function prototypes
 *          for better modularity and readability in the project. It ensures that these functions
 *          can be correctly referenced and utilized in different parts of the program.
 *
 *          Function Prototypes:
 *          - void u1_1(): Calculate and display prices with VAT.
 *          - void u1_2(): Process and categorize student grades.
 *          - void u1_3(): Convert foreign currency amount to CZK.
 *
 * @see functions.cpp for the implementation of these functions.
 *
 * @see https://github.com/Jekwwer/ZSP-Project01-2023 for more project details.
 *
 * @author Evgenii Shiliaev
 * @date October 29, 2023 (Creation)
 *       November 13, 2023 (Comment enhancements)
 */

#ifndef ZSP_FUNCTIONS01_H
#define ZSP_FUNCTIONS01_H
#include <stdio.h>

/**
 * @brief Calculates and displays prices with VAT.
 * @details This function prompts the user to enter the number of items and the price per item,
 *          then calculates and displays the total price with and without a 20% VAT.
 * @note Used for demonstrating basic arithmetic operations and user input handling in C++.
 */
void u1_1();

/**
 * @brief Processes student grades and determines grade status.
 * @details This function accepts five student grades as input, calculates the average grade,
 *          and categorizes the result as pass with distinction, pass, or fail based on the average.
 * @note Showcases array handling, conditional logic, and basic mathematical operations in C++.
 */
void u1_2();

/**
 * @brief Converts a given amount of foreign currency into Czech Koruna (CZK).
 * @details This function prompts the user for a currency abbreviation, its exchange rate to CZK,
 *          and the amount to be converted, then calculates and displays the total value in CZK.
 * @note Demonstrates string handling, floating-point arithmetic, and rounding operations in C++.
 */
void u1_3();

#endif // ZSP_FUNCTIONS01_H

/** End of functions.h */