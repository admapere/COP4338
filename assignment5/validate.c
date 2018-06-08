/* 
 *     Source: validate.c
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
#include "validate.h"

/*
 * Function: parse_date
 *  Purpose: gets an input string, parses the input into an array of ints
 *	which represent the month, day, and year. 
 *
 *  @params: date as a string to be parsed
 *  @return: the total correctly parsed tokens
 */
int parse_date(int *date_arr, const char *date){
	#define MAX_TOK 3
	int parsed_tokens = 0;
	int iter = 0;
	long token = 0;
	char buf[BUFSIZ] = {'\0'};
	char *tailptr = NULL;

	while (sscanf(date, "%[^/]%n", buf, &iter) == 1){
		errno = 0;
		token = strtol(buf, &tailptr, NUM_BASE);
		parsed_tokens++;
		
		/*bound checking for the years*/
		if (errno == ERANGE || token > INT_MAX || token < INT_MIN){
			fprintf(stderr, "ERROR: %s %s [%d , %d]\n", buf,
			"too large. Years can only range", INT_MIN, INT_MAX);
			
			return FALSE;
		}//end if

		/*checks if buffer is not int*/		
		if (buf == tailptr){
			fprintf(stderr, "ERROR: %s %s [%d , %d] \n", buf,
			"is invalid year. Only values in", INT_MIN, INT_MAX);
			return FALSE;
		}//end if

		/*checks if there are too many inputs*/
		if (parsed_tokens > MAX_TOK){
			return FALSE;
		}//end if

		*date_arr = token;
		date_arr++;
		date += iter + 1;
	}//end loop
	

	return TRUE;
	#undef MAX_TOK
}//end function
/*
 * Function: is_valid_date
 *  Purpose: determines whether input date is a correct date
 *	static char daytab idea is taken from The C Programming Language
 *	by Brian Kernighan and Dennis Ritchie on page 111
 *  
 *  @params: int[] represents a date in the MM/DD/YYYY format
 *  @return: boolean determining if it is a valid date 
 */
int is_valid_date(const int date[]){
	#define MONTH 0
	#define DAY 1
	#define YEAR 2
	int lyear = FALSE;
	static char daytab[2][13]= {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};
	
	lyear = is_leap_year(date[YEAR]);
	if ((date[MONTH] < MIN_MONTH) || (date[MONTH] > MAX_MONTH)){
		return FALSE;
	}//end if

	if (date[DAY] > daytab[lyear][date[MONTH]] || date[DAY] < MIN_DAY){
		return FALSE;
	}//end if
	
	return TRUE;
	#undef MONTH
	#undef DAY
	#undef YEAR
}//end function
/*
 * Function: is_leap_year
 *  Purpose: calculates whether the input value is a leap year.
 *
 *  A year is a leap year if the following evaluates to true.
 *  https://en.wikipedia.org/wiki/Leap_year#Algorithm
 *
 *  @params: year
 *  @return: whether a year is a leap year or not.
 */
int is_leap_year(int year){
	if (year % 4 != 0){
		return FALSE;
	}//end if

	if (year % 100 != 0){
		return TRUE;
	}//end if

	if (year % 400 != 0){
		return FALSE;
	}//end if

	return TRUE;
}//end function
/*
 * Function: date_invalid_err
 *  Purpose: procedure that prints if a date is incorrect
 *  
 *  @params: the offending string 
 *  @return: 
 */
void date_invalid_err(const char *date){
	fprintf(stderr, "ERROR: '%s' %s\n", date, "is invalid");
}//end function
