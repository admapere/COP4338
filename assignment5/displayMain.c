/* 
 *     Source: displayMain.c
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
 *
 * ========================================================================
 *
 * Description:	This program takes in correctly formatted dates from stdin
 *	 and prints them out in DD MMM YYYY format
 *
 *       Input: The output should be piped into the program and correctly
 *       formatted.
 *
 *      Output: The output is all input dates formatted in the DD MMM YYYY
 *      format, as well as the original list of dates appended at the end.
 *
 *     Process: 
 *	(1) The program takes in an input line
 *	(2) Formats the input date to the correct input
 *	(3) Prints to stdout the correct format
 *
 * Required Features: All required features implemented
 *
 * Known Bugs: None
 */

#include "display.h"

int main(void){
	char buf[BUFSIZ];
	struct Date date = {0, 0, 0};
	int iter = 0;
	
	/*tokenizes stdin per line*/
	while (fgets(buf, sizeof buf, stdin) != NULL){
		create_date(&date, buf);
		to_string(&date, buf, sizeof (buf));
		printf("%s\n", buf);
		
		/*set pointer to stdin to next; reset buffer*/
		memset(buf, '\0', iter);
	}//end while

	print_original_file();

	return EXIT_SUCCESS;
}//end function

void print_original_file(){
	FILE *fileptr = NULL;
	char buf[BUFSIZ] = {'\0'};
	
	fileptr = fopen("dates.dat", "r");//USED TO BE data.dat
	fscanf(fileptr, "%[^EOF]", buf);
	printf("\n%s", buf);
	fclose(fileptr);
}//end function 
