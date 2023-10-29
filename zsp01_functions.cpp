/**
 * @file zsp01_functions.cpp
 * @brief Implementation for ZSP VŠPJ 1st Homework Assignment.
 *
 * This source file contains the implementation of functions and methods required
 * to complete the 1st homework assignment in the ZSP VŠPJ (Fundamentals of Structural Programming) course.
 *
 * This file is NOT part of the submitted solution.
 * It's meant only for debugging and testing purposes.
 *
 * @see https://github.com/Jekwwer/ZSP-Homework01-2023
 *
 * @author Evgenii Shiliaev
 * @date October 29, 2023
 */

#include "zsp01_functions.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Function for Task u1.1.
 *
 * Task 1 (u1_1)
 * Calculate purchase price (with and without VAT) based on user input.
 * Input: Number of pieces (integer) and the price per piece (integer)
 * Output: Display item price, total without VAT, and total with VAT
 *         (integer rounded according to mathematical rules).
 *
 * VAT  = 20%. (const)
 *
 * @return nothing
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
        price_w_vat = (int)price * VAT + 1;
    }
    else
    {
        price_w_vat = (int)price * VAT;
    }

    printf("Účtenka\n");
    printf("Cena bez DPH/ks %d Kč\tCena s DPH/ks %d Kč\n", price, price_w_vat);
    printf("Počet kusů: %d\tCena bez DPH %d Kč\tCena s DPH (20 %%) %d Kč\n", count, price * count, price_w_vat * count);
}

/**
 * @brief Function for Task u1.2.
 *
 * Task 2 (u1_2)
 * User inputs 5 grades.
 * Calculate average and grade status (pass with distinction, pass, fail).
 * Output: Display marks, average, and grade status.
 *
 * @return nothing
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

void u1_3()
{
    // todo u1-3
}

/** End of zsp01_functions.cpp */