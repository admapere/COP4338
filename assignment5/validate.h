/* 
 *     Source: validate.h
 *     Author: Adrian Manuel Perez
 *      StuID: 3180957
 * Assignment: Program #5 Date Validation and Display
 *
 *     Course: COP 4338 (Advanced Programming)
 *    Section: U01
 *   Due Date: 3 APR 2018, 6:25 PM
 *
 *	I hereby certify that this collective work is my own
 *	and none of it is the work of any other person or entity.
 *	___________________________________________________
 *
 *    Language: C
 * Compile/Run:
 *	DEPENDENCIES: must be in same directory!
 *	validate.c validateMain.c
 *	display.c displayMain.c
 *	display.h validate.h data.dat makefile
 *
 *	COMPILATION:
 *	$ make all
 *	OR
 *	$ make validate
 *	$ make display
 *	OR
 *	$ gcc -o validateMain.out validateMain.c validate.c
 *	$ gcc -o displayMain.out displayMain.c display.c
 *	
 *	RUN: [n] - max number of correclty formated prints. 0 means all
 *	$ ./validateMain.out < data.dat [n] | displayMain.out > output.dat
 */

#ifndef VALIDATE_H
#define VALIDATE_H

#include <stdio.h>
#include <stdlib.h>//EXIT_SUCCESS, EXIT_FAILURE, exit
#include <string.h>//memset
#include <limits.h>//INT_MAX
#include <errno.h>//ERANGE

#define NUM_BASE 10
#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_MONTH 1
#define MAX_MONTH 12
#define length_of(arr) (sizeof(arr) / sizeof(arr[0]))

enum Boolean{FALSE, TRUE};

int parse_date(int *date_arr, const char *date);
int is_valid_date(const int date[]);
int isnumber(const char *input_string);
int is_leap_year(int year);
int verify_inputs(int argc, const char **argv, int *count);
void date_invalid_err(const char *date);

#endif /*VALIDATE_H*/
