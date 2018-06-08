/*=========================================================================
|   Source Code: [source]
|        Author: [student]
|    Student ID: [studentid]
|    Assignment: [asignment]
| 
|        Course: [course]
|       Section: [section]
|    Instructor: [instructor]
|      Due Date: [duedate]
|   
|   I hereby certify that this collective work is my own
|   and none of it is the work of any other person or entity.
|   ______________________________________________[Signature]
|
|      Language: [language]
|   Compile/Run: [instructions]
|   
|+-------------------------------------------------------------------------
|
|   Description: [description]
|         Input: [input]
|        Output: [output]
|       Process: [algorithm]
|  Missing Features: [missingfeatures]
|    Known Bugs: [bugs]
|*=======================================================================*/

/*INCLUDES*/
#include <stdio.h>
#include <math.h>

/*DEFINES*/
#define MIN_INTERVAL 1
#define MAX_INTERVAL 1000
#define MAX_ERROR 16

/*GLOBAL CONSTANTS*/
enum boolean{FALSE, TRUE};

/*PROTOTYPES*/
double babSqrtInit(double);
double babSqrt(double, double, int);
int    factorize(int);
int    isPerfect(int);
int    sum(int);

/*MAIN*/

int main(void){
	return 1;
}

/*SUBROUTINES*/

/* ========================================================================
 * function: babSqrtInit
 *  purpose: sets the initial parameters for the recursive call of babSqrt
 *
 *  @params: number the number for which we want to find the squareroot
 *           log(n) the initial guess for the sqrt; natural log was chosen
 *           because ln(x) < sqrt(x) for all x > 1
 *
 *  @return: double the square root of the input value
 * ======================================================================*/

double babSqrtInit(double number)
{
	return babSqrt(number, log(number), TRUE); 
}

/* ========================================================================
 * function: babSqrt 
 *  purpose: calculates the square root of a number recursively using the
 *           babylonian method:
 *           let X be an initial guess
 *           Let S be the number we want to find the square root of
 *           Xn+1 = 0.5 * (Xn + (S / Xn)
 *           ...
 *           sqrt(S) = lim n -> infinity of Xn
 * 
 *  @params: number       the number we want to calculate the square root
 *           initialGuess the initial guess for the square root
 *           index        number of iterations before desired accuracy
 *
 *  @return: square root of the input number
 * ======================================================================*/

double babSqrt(double number, double initialGuess, int isFirst)
{
	static double  calcNumber, runningSqrt;
	static int     firstTime, index;

	/*Initializes static variables the for the first recursive call;
	* isFirst should have a value of FALSE every other time*/
	if(isFirst)
	{
		calcNumber  = number;
		runningSqrt = initialGuess;
		firstTime   = FALSE;
		index       = MAX_ERROR;
	}

	if(index == 0)
	{
		return runningSqrt;
	}
	else
	{
		runningSqrt = (0.5) * ( runningSqrt + ( calcNumber / runningSqrt));
		index--;

		return babSqrt(calcNumber, runningSqrt, firstTime);
	}
}

/* ========================================================================
 * function: 
 *  purpose:
 *
 *  @params:
 *
 *  @return:
 * ======================================================================*/

int isPerfect(int number){
	return;
}

/* ========================================================================
 * function:
 *  purpose:
 *
 *  @params:
 *  @return:
 * ======================================================================*/

int factorize(int i1){
	return;
}

/* ========================================================================
 * function:
 *  purpose:
 *
 *  @params:
 *  @return:
 * ======================================================================*/

int sum(int i1){
	return;
}
