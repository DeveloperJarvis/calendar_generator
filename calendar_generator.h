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
#ifndef CALENDAR_GENERATOR_H
#define CALENDAR_GENERATOR_H

#include <stdbool.h> // for bool datatype

// --------------------------------------------------
// global variables
// --------------------------------------------------
int year;              // Store the given year
int month;             // Store the given month
int start_day;         // The starting day of the month (from 0 for Sunday to 6 for Saturday)
int num_days_in_month; // Number of days in the given month

const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   // days in year
                                                                                // later adjusted for leap year
const char *days_of_week[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; // days of week in string
const char *months_of_year[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
                                "Sep", "Oct", "Nov", "Dec"}; // Months of Year
// --------------------------------------------------
// forward function declarations/ prototypes
// --------------------------------------------------
void display_help(const char *s);
void display_version(const char *s);

void calendar_generator();
void user_input();
void clear_input_buffer();
bool validate_input(int year, int month);
bool check_leap(int year);
int number_days_in_month(int month, int year);
int calculate_start_day_of_the_month(int month, int year);
void display_calendar(int start_day, int num_days_in_month);
#endif
