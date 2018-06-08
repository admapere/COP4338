/* 
 *     Source: display.h
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

#ifndef DISPLAY_H
#define DISPLAY_H

#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_MONTH 1
#define MAX_MONTH 12
#define length_of(arr) (sizeof(arr) / sizeof(arr[0]))

#include <stdio.h>
#include <stdlib.h>//atoi
#include <string.h>//strcpy, strtok, strlen

enum Boolean{FALSE, TRUE};

struct Date{
	int day;
	int month;
	int year;
};
struct Date *create_date(struct Date *date, char *date_str);
size_t to_string(const struct Date *date, char *buf, size_t buflen);
void print_original_file(void);

#endif /*DISPLAY_H*/
