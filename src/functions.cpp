/**
 * @file functions.cpp
 * @brief Implementation of functions for ZSP VŠPJ 1st Homework Assignment.
 * @details This file provides the detailed implementation of various functions required
 *          for the completion of the first homework assignment in the ZSP VŠPJ course.
 *          It includes functions for calculating prices with VAT, processing student grades,
 *          and performing currency conversions. Each function is tailored to specific
 *          requirements outlined in the assignment, demonstrating fundamental programming
 *          concepts in C.
 *
 *          Examples:
 *          - A function for calculating prices with VAT includes user input handling and
 *            arithmetic operations to determine final prices.
 *          - The grade processing function demonstrates array usage and conditional logic
 *            to categorize student performance.
 *          - Currency conversion function uses basic input/output operations and arithmetic
 *            to provide the monetary conversion.
 *
 *          These implementations are foundational examples of using C for solving
 *          real-world problems in a structured manner.
 *
 * @note This file is part of the educational coursework and is not intended for
 *       production use. It is structured to provide clear examples of basic C functionality.
 *
 * @code
 * // Example usage of a function
 * int main() {
 *     u1_1(); // Function call for calculating prices with VAT
 *     return 0;
 * }
 * @endcode
 *
 * @see functions.h for the declaration of these functions.
 * 
 * @see https://github.com/Jekwwer/ZSP-Project01-2023 for more details about the project.
 *
 * @author Evgenii Shiliaev
 * @date October 29, 2023 (Creation)
 *       November 13, 2023 (Comment enhancements)
 */

#include "functions.h"

/**
 * @brief Calculates purchase prices with and without VAT.
 *
 * @details This function takes the number of items and price per item as input and calculates
 *          the total cost both with and without VAT. The VAT rate is set at 20%. It's designed to
 *          demonstrate basic arithmetic operations and input handling in C.
 *
 *          Example:
 *          If the user inputs 5 items each costing 100 units, the function will output
 *          500 units as the total without VAT and 600 units as the total with VAT.
 *
 * @param count The number of items to be purchased (as an integer).
 * @param price The price per item (as an integer).
 *
 * @pre The function expects non-negative integer values for 'count' and 'price'.
 *
 * @post Outputs the total price without VAT and with VAT to the standard output.
 *
 * @note This function is primarily used for educational purposes to illustrate basic
 *       C functionalities like arithmetic operations and input/output.
 *
 * @code
 * int main() {
 *     u1_1(); // Function call for calculating prices with VAT
 *     return 0;
 * }
 * @endcode
 *
 * @todo Refine the rounding logic for VAT calculation to handle edge cases.
 *
 * @warning Ensure that the input values for 'count' and 'price' are non-negative to avoid
 *          incorrect calculations.
 */

void u1_1()
{
    const double VAT = 1.2;

    int count = 0;
    int price = 0;
    int price_w_vat = 0;
    scanf("%d %d", &count, &price);

    if (price * VAT - (int)(price * VAT) >= 0.5)
    {
        price_w_vat = (int)(price * VAT) + 1;
    }
    else
    {
        price_w_vat = (int)(price * VAT);
    }

    printf("Účtenka\n");
    printf("Cena bez DPH/ks %d Kč\tCena s DPH/ks %d Kč\n", price, price_w_vat);
    printf("Počet kusů: %d\tCena bez DPH %d Kč\tCena s DPH (20 %%) %d Kč\n", count, price * count, price_w_vat * count);
}

/**
 * @brief Processes student grades and determines grade status.
 *
 * @details This function takes five student grades as input and calculates the average grade.
 *          It then determines the grade status based on predefined criteria: pass with distinction
 *          (average <= 1.50), pass (average <= 4.00), or fail (average > 4.00). It's designed to
 *          demonstrate array handling, conditional logic, and basic mathematical operations in C.
 *
 *          Example:
 *          If the user inputs grades 2, 3, 2, 1, and 2, the function will calculate the average
 *          as 2.0, and determine that the student has passed but without distinction.
 *
 * @pre The function expects five integer input values between 1 (best grade) and 5 (worst grade).
 *
 * @post Outputs the individual grades, calculated average, and grade status to the standard output.
 *
 * @note This function is primarily used for educational purposes to illustrate the handling of arrays,
 *       basic user input, and conditional statements in C.
 *
 * @code
 * int main() {
 *     u1_2(); // Function call for processing student grades
 *     return 0;
 * }
 * @endcode
 *
 * @todo Implement input validation to ensure grades are within the specified range.
 *
 * @warning Incorrect input (grades outside the range 1-5) can lead to erroneous calculations and status determination.
 */

void u1_2()
{
    const int BEST_GRADE = 1;
    const int WORST_GRADE = 5;
    const double PASS_BORDER = 4.00;
    const double DISTINCTION_BORDER = 1.50;

    int grades[5] = {0, 0, 0, 0, 0};
    scanf("%d %d %d %d %d", &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]);

    printf("Známky: %d\t%d\t%d\t%d\t%d\n", grades[0], grades[1], grades[2], grades[3], grades[4]);

    double average_grade = 0;
    for (int i = 0; i < 5; i++)
    {
        average_grade += grades[i];
    }
    average_grade /= 5;
    printf("%.2f\n", average_grade);

    if (average_grade < BEST_GRADE && average_grade > WORST_GRADE)
    {
        printf("ERROR\n");
    }

    printf("Prospěl s vyznamenáním: ");
    if (average_grade >= BEST_GRADE && average_grade <= DISTINCTION_BORDER)
    {
        printf("1:Ano\n");
    }
    else
    {
        printf("0:Ne\n");
    }

    printf("Prospěl: ");
    if (average_grade >= BEST_GRADE && average_grade <= PASS_BORDER)
    {
        printf("1:Ano\n");
    }
    else
    {
        printf("0:Ne\n");
    }

    printf("Neprospěl: ");
    if (average_grade > PASS_BORDER && average_grade <= WORST_GRADE)
    {
        printf("1:Ano\n");
    }
    else
    {
        printf("0:Ne\n");
    }
}

/**
 * @brief Converts a given amount of foreign currency into Czech Koruna (CZK) based on user input.
 *
 * @details This function prompts the user to input a currency abbreviation (e.g., USD, EUR), the exchange rate
 *          against the CZK, and the amount of foreign currency to be converted. It then calculates and displays
 *          the total value in CZK, rounding to the nearest integer. This function serves as a practical example
 *          of handling user input, performing arithmetic calculations, and rounding results in C++.
 *
 *          Example:
 *          If the user inputs 'USD', an exchange rate of 22.5, and an amount of 100, the function calculates
 *          the total as 2250 CZK (assuming no decimal fractions).
 *
 * @pre The function expects the user to enter valid and realistic data for currency conversion.
 *
 * @post The function outputs the equivalent amount in CZK, based on the user-inputted exchange rate and amount.
 *
 * @note This function can be adapted to include more sophisticated currency conversion features, such as handling
 *       different decimal precisions or supporting a wider range of currencies.
 *
 * @code
 * int main() {
 *     u1_3(); // Function call for currency conversion
 *     return 0;
 * }
 * @endcode
 *
 * @todo Implement a feature to fetch real-time exchange rates from a financial API for more accurate conversions.
 *
 * @warning Incorrect or unrealistic user input values can lead to erroneous conversion results. Always ensure
 *          the inputs are realistic and valid.
 */
void u1_3()
{
    char currency_name[256] = {0}; // Initialize the array with zeros
    double currency_value = 0;
    int count = 0;
    scanf("%s %lf %d", currency_name, &currency_value, &count);

    int rounded_result = 0;
    if (currency_value * count - (int)(currency_value * count) >= 0.5)
    {
        rounded_result = (int)(currency_value * count) + 1;
    }
    else
    {
        rounded_result = (int)(currency_value * count);
    }

    printf("1 %s = %.1f Kč\n", currency_name, currency_value);
    printf("Nákup: %d %s\n", count, currency_name);
    printf("Celkem: %d x %.1f = %.1f Kč Zaokrouhleno: %d Kč\n", count, currency_value, count * currency_value,
           rounded_result);
}

/** End of functions.cpp */