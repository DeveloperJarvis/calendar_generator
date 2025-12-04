// --------------------------------------------------
// -*- C -*- Compatibility Header
//
// Copyright (C) 2023 Developer Jarvis (Pen Name)
//
// This file is part of the [Project Name] Library. This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// calendar_generator - Print calendar for any month and year
//
// Author: Developer Jarvis (Pen Name)
// Contact: https://github.com/DeveloperJarvis
//
// --------------------------------------------------

// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h>   // for printf(), scanf()
#include <string.h>  // for strcmp()
#include <stdbool.h> // for bool datatype

#include "calendar_generator.h"

// --------------------------------------------------
// main function
// --------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
            display_help(argv[0]);
        else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
            display_version(argv[0]);
    }
    else if (argc == 1)
        calendar_generator();
    else
    {
        printf("Invalid input\n");
        display_help(argv[0]);
    }
    return 0;
}

// --------------------------------------------------
// helper function
// --------------------------------------------------
// Displays usage and help
void display_help(const char *s)
{
    printf("Usage: %s [options]\n", s);
    printf(" -h --help\tDisplay help\n");
    printf(" -v --version\tDisplay version\n");
}

// Displays program version
void display_version(const char *s)
{
    printf("%s version: 1.0.0\n", s);
}

// --------------------------------------------------
// calendar generation core
// --------------------------------------------------
// Main calendar generator logic
void calendar_generator()
{
    user_input();
    // bool check = check_leap(year); // true: leap, false: not a leap
    bool valid = validate_input(year, month);
    if (valid)
    {
        start_day = calculate_start_day_of_the_month(month, year);
        num_days_in_month = number_days_in_month(month, year);
        printf("Calendar:\n\t\t\t%s\t%d\n\n", months_of_year[month - 1], year);
        display_calendar(start_day, num_days_in_month);
    }
    else
    {
        printf("Invalid entry for month and year. Unable to generate the calendar\n");
    }
}

// Accepts the year and the month for which the calendar needs to be generated
void user_input()
{
    int input;
    while (1)
    {
        printf("Please enter the year you want the calendar to be generated:\n");
        if (scanf("%d", &input) != 1)
        {
            printf("Invalid Input. Please enter a valid integer\n");
            clear_input_buffer();
            continue;
        }
        if (input < 1000 || input > 9999)
        {
            printf("Please enter a 4 digit positive number as year\n");
            continue;
        }
        else
        {
            year = input;
            break;
        }
    }
    input = 0;
    while (1)
    {
        printf("Please enter the month of the year to be generated:\n");
        if (scanf("%d", &input) != 1)
        {
            printf("Invalid Input. Please enter a valid integer\n");
            clear_input_buffer();
            continue;
        }
        if (input < 1 || input > 12)
        {
            printf("Please enter a choice between 1 and 12 as month\n");
            continue;
        }
        else
        {
            month = input;
            clear_input_buffer();
            break;
        }
    }
}

// Clears the input buffer until newline or end of file is reached
void clear_input_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ; // Clear input buffer
}

// Check if the month is between 1 and 12, and if the year is a positive integer.
// True if valid, False if not
bool validate_input(int year, int month)
{
    if ((month >= 1 && month <= 12) && year > 0)
        return true;
    return false;
}

// Applies the leap year rules to return True/False.
// True if the year is a leap year, False otherwise
bool check_leap(int year)
{
    if (year % 4 != 0)
        return false;
    else if (year % 4 == 0)
    {
        if (year % 400 == 0)
            return true;
        else if (year % 100 == 0)
            return false;
        else
            return true;
    }
}

// Return the correct number of days in the month, accounting for leap years in February.
// Number of days in the given month
int number_days_in_month(int month, int year)
{
    int days;
    if (month == 2 && check_leap(year)) // leap year Feb
        return 29;
    return days_in_month[month - 1]; // months are 1 to 12, index are from 0
}

/*
 * Source: https://en.wikipedia.org/wiki/Zeller%27s_congruence
 * Zeller's congruence is an algorithm devised by Christian Zeller in the 19th century to
 * calculate the day of the week for any Julian or Gregorian calendar date. It can be
 * considered to be based on the conversion between Julian day and the calendar date.
 *
 * Zeller's Congruence (Gregorian calendar)
 *
 * Formula:
 *     h = ( q
 *         + floor( 13 * (m + 1) / 5 )
 *         + K
 *         + floor( K / 4 )
 *         + floor( J / 4 )
 *         - 2 * J
 *       ) mod 7
 *
 * For the Julian calendar:
 *     h = ( q
 *         + floor( 13 * (m + 1) / 5 )
 *         + K
 *         + floor( K / 4 )
 *         + 5
 *         - J
 *       ) mod 7
 *
 * Definitions:
 *     h = day of week
 *         0 = Saturday
 *         1 = Sunday
 *         2 = Monday
 *         ...
 *         6 = Friday
 *
 *     q = day of month
 *
 *     m = month
 *         3 = March
 *         4 = April
 *         ...
 *         14 = February
 *
 *     K = year of the century
 *         (adjYear % 100)
 *
 *     J = zero-based century
 *         floor(adjYear / 100)
 *
 *     floor(x) = integer part of x
 *     mod = modulo operation
 *
 * Note:
 *     January and February are treated as months 13 and 14 of the previous year.
 *     Example:
 *         Date: 02/02/2010 (2 Feb 2010)
 *         Use:  q = 2, m = 14, adjYear = 2009
 *
 *     adjYear =
 *         actual year     (for March–December)
 *         previous year   (for January–February)
 *
 * ISO day-of-week (1 = Monday … 7 = Sunday):
 *     d = ((h + 5) mod 7) + 1
 */

// This function calculates which day of the week the 1st of the month falls on using an \
// algorithm like Zeller’s Congruence.
// Start day of the week as an integer, e.g., 0 for Sunday, 6 for Saturday
int calculate_start_day_of_the_month(int month, int year)
{
    // q is Day of month (which will be 1 for all)
    int q = 1;
    // m is month starting Mar: 3 ... till Dec: 12 then Jan: 13 and Feb: 14
    int m = ((month == 1 || month == 2) ? month + 12 : month);
    // adjYear is actual year (for Mar to Dec) and previous year (for Jan and Feb)
    int adjYear = ((month == 1 || month == 2) ? year - 1 : year);

    int K = adjYear % 100; // Year of century
    int J = adjYear / 100; // Zero-based century

    // Zeller's congruence (Georgian)
    // h is day of week
    int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    // Convert Zeller to ISO day of week
    // 1 = Monday ... 7 = Sunday
    int d = ((h + 5) % 7) + 1;

    return ((d == 7) ? 0 : d); // convert Sun to index 0
}

// This function prints the formatted calendar. It fills in the correct days of the week in a \
// 7-column grid.
void display_calendar(int start_day, int num_days_in_month)
{
    if ((start_day >= 0 && start_day <= 7) &&
        (num_days_in_month >= 28 && num_days_in_month <= 31))
    {
        int date = 1;
        int i, j, k;

        for (i = 0; i < 7; i++)
            printf("\t%s", days_of_week[i]);
        printf("\n");
        int rows = ((num_days_in_month == 28) ? (num_days_in_month / 7) : (num_days_in_month / 7 + 1));
        for (i = 0; i < rows; i++)
        {
            if (start_day > 0 && date == 1)
            {
                for (j = 0; j < start_day; j++)
                    printf("\t ");
                k = start_day;
            }
            else
                k = 0;
            for (; k < 7; k++)
            {
                if (date > num_days_in_month)
                    break;
                printf("\t%d", (date));
                date++;
            }
            printf("\n");
        }
    }
    else
    {
        printf("Some error occured displaying calendar\n");
    }
}
