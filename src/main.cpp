/**
 * @file main.cpp
 * @brief Application entry point for ZSP VŠPJ 1st Homework Assignment.
 * @details This file contains the main function and serves as the entry point for the application.
 *          It is a part of the solution to the 1st homework assignment in the ZSP VŠPJ
 *          (Fundamentals of Structural Programming) course. The main function in this file
 *          sequentially invokes the functions `u1_1`, `u1_2`, and `u1_3`, demonstrating their
 *          functionality as part of the assignment requirements.
 *
 *          This file is utilized primarily for debugging and testing purposes, and it demonstrates
 *          the integration and execution of individual tasks defined in the project.
 *
 * @see functions.h for the declaration of the functions `u1_1`, `u1_2`, and `u1_3`.
 *
 * @see https://github.com/Jekwwer/ZSP-Project01-2023 for the project repository.
 *
 * @author Evgenii Shiliaev
 * @date October 29, 2023 (Creation)
 *       November 13, 2023 (Comment enhancements)
 */

#include "functions.h"

/**
 * @brief Main function of the application.
 * @details Initializes the application and executes the primary logic. This function is the
 *          starting point of the program and sequentially calls the functions `u1_1`, `u1_2`,
 *          and `u1_3`. Each call demonstrates the functionality of these functions as per the
 *          homework assignment. The output of these functions represents the core processing
 *          performed in the program.
 *
 *          The following tasks are executed:
 *          - u1_1: Calculation of prices with VAT.
 *          - u1_2: Processing of student grades.
 *          - u1_3: Conversion of currency to Czech Koruna (CZK).
 *
 * @note Primarily used for testing and demonstrating the integrated functionality of the individual tasks.
 *
 * @return Returns 0 upon successful completion of the program.
 */
int main()
{
    printf("Evgenii Shiliaev\nshilia01\n29.10.2023\n");
    u1_1(); // Task 01 - Price Calculation with VAT
    u1_2(); // Task 02 - Student Grade Processing
    u1_3(); // Task 03 - Currency Conversion
    return 0;
}

/** End of main.cpp */