/* 
 *     Source: validateMain.c
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
 *	validate.c validateMain.c display.c displayMain.c 
 *	display.h validate.h data.dat makefile
 *
 * COMPILATION:
 *	$ make all
 *	OR
 *	$ make validate
 *	$ make display
 *	OR
 *	$ gcc -o validateMain.out validateMain.c validate.c
 *	$ gcc -o displayMain.out displayMain.c display.c
 *	
 * RUN: [n] - max number of correclty formated prints. 0 means all
 *	$ ./validateMain.out < data.dat [n] | displayMain.out > output.dat
 *
 *+========================================================================
 *
 * Description: This program validates dates from stdin. If the dates
 *	conform to MM/DD/YYYY formats, and are valid dates, the dates are
 *	then printed out to stdout.
 *
 * Input: The user is required to input a number from 0 to INT_MAX which
 *	determines how many correctly parsed dates to be printed out. 0 is
 *	a special input which designates all valid dates to be printed.
 *
 * Output: The program prints out all the correctly parsed and valid dates
 *	It may further print out to stderr any failed parsings with a brief
 *	explanation as to why they failed to be parsed.
 *
 * Process:
 *	(1) command line input determines how many lines to print
 *		(1.1) any errors in command line input exit program
 *	(2) gets input from stdin, line by line
 *	(3) parses each individual line. 
 *	(4) if line does not conform to MM/DD/YYYY format,
 *	an exception occurs
 *	(5) prints out each correctly formatted date to stdout
 *
 * Required Features: All features included
 *
 * Known Bugs: leading spaces in date lead to incorrect parsing
 *	i.e. 1 2/ 1  6/1991 produces 1 JAN 1991 instead of 16 DEC 1991
 */
#include "validate.h"

int main(int argc, const char **argv)
{
	char buf[BUFSIZ] = {'\0'};
	int iter = 0;
	int date[] = {0, 0, 0};
	int desired_prints = 0;
	int count = 0;
	verify_inputs(argc, argv, &desired_prints);
	
	/*parses stdin into lines*/
	while ((scanf("%[^\n]%n", buf, &iter) == 1) && (count != desired_prints)){
		int correctly_parsed = parse_date(date, buf);
		int valid_date = is_valid_date(date);
		if (!correctly_parsed || !valid_date){
			date_invalid_err(buf);
		}else{
			printf("%s\n", buf);
			count++;
		}//end if
		
		/*resets buffer and stream for next token*/
		fseek(stdin, 1, SEEK_CUR);
		memset(buf, '\0', iter);
	}
	return EXIT_SUCCESS;
}//end function
/*
 * Function: verify_inputs 
 *  Purpose: 
 *
 *  @params: argc count of command line arguments
 *	   **argv arguments from command line
 *	   *count pointer to variable count of printed outpute 
 *  @return: bool representing a successful verification
 */
int verify_inputs(int argc, const char **argv, int *count){
	#define EXPECTED_ARG_COUNT 2
	#define PRINTS 1
	
	/*various bounds checking for amount of command line armguments*/
	if (argc > EXPECTED_ARG_COUNT){
		fprintf(stderr, "%s %s [%d , %d]\n",
		"ERROR: Too many arguments,",
		"expected a single integer in the range", 0, INT_MAX);
		
		exit(EXIT_FAILURE);
	}//end if
	if (argc < EXPECTED_ARG_COUNT){
		fprintf(stderr, "%s %s [%d , %d]\n",
		"ERROR: Too few arguments,",
		"expected a single integer in the range", 0, INT_MAX);
		
		exit(EXIT_FAILURE);
	}//end if
	
	/*error checking for argument itself*/
	char *tailptr = NULL;
	*count = strtol(*(argv + PRINTS), &tailptr, NUM_BASE);
	if (tailptr == *(argv + PRINTS)){
		fprintf(stderr, "%s %s [%d , %d]\n",
		"ERROR: non-numeric character found",
		"expected a single integer in the range", 0, INT_MAX);
		
		exit(EXIT_FAILURE);
	}//end if

	if (*count < 0){
		fprintf(stderr, "%s %s [%d , %d]\n",
		"ERROR: negative number found",
		"expected a single integer in the range", 0, INT_MAX);

		exit(EXIT_FAILURE);
	}//end if

	if (*count == 0){
		*count = INT_MAX;//user wants max allowable prints
	}//end if

	return TRUE;  
	#undef PRINTS
	#undef EXPECTED_ARG_COUNT
}//end function
