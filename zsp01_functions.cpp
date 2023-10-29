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
 * @brief Function for Task U1.1.
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

void u1_2()
{
    // todo u1-2
}

void u1_3()
{
    // todo u1-3
}

/** End of zsp01_functions.cpp */