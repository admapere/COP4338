/* 
 *     Source: display.c
 *     Author: Adrian Manuel Perez
 *      StuID: 3180957
 * Assignment: Program #5 Date Validation and Display
 *
 *     Course: COP 4338 (Advanced Programming)
 *    Section: U01
 * Instructor: William Feild
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

#include "display.h"

/*
 * Function: create_date
 *  Purpose: Sets struct elements to correct day, month, and year.
 *
 *  @params: *date pointer to a date to create
 *	     day   value in [DAY_MIN, DAY_MAX]
 *	     month value in [MONTH_MIN, MONTH_MAX]
 *	     year  value in [INT_MIN, INT_MAX]
 *
 *  @return: whether the function executed correctly, or threw an error
 */
struct Date *create_date(struct Date *date, char *date_str){
	char *delim = "/";
	char *token = NULL;
	int day = 0;
	int month = 0;
	int year = 0;

	token = strtok(date_str, delim);
	month = atoi(token);
	token = strtok(NULL, delim);
	day = atoi(token);
	token = strtok(NULL, delim);
	year = atoi(token);

	date->day = day;
	date->month = month;
	date->year = year;

	return date;
}//end function
/*
 * Function: to_string
 *  Purpose: fills input buffer with a string of a Date object
 *
 *  @params: *date  pointer to date to represent as a string
 *	     *buf   pointer to buffer to fill with a string 
 *	     buflen length of destination buffer
 *
 *  @return: the length of the string representation
 */
size_t to_string(const struct Date *date, char *buf, size_t buflen){
	#define NUM_BASE 10 //number of numerals in decimal system
	#define INT_MASK 0x30 //ASCII for integers
	const char *MONTHS[] = {"ERR", "JAN", "FEB", "MAR", "APR", "MAY",
			"JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
	int day = date->day;
	int month = date->month;
	int year = date->year;
	char *iter = buf;
	
	/*sets day string representation*/
	if (day < NUM_BASE){
		*iter = ' ';
		iter++;
	}else{
		*iter = (day / NUM_BASE) + INT_MASK;
		iter++;
	}//end if
	*iter = (day % NUM_BASE) + INT_MASK;
	iter++;
	*iter = ' ';
	iter++;
	
	/*sets month string representation*/
	strcpy(iter, MONTHS[month]);
	iter += strlen(MONTHS[month]);
	*iter = ' ';
	iter++;
	
	/*sets year string representation*/
	sprintf(iter, "%d", year);

	return (size_t)(iter - buf);
}//end function
