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
#define MAX_INTERVAL 10000
#define MAX_DIVISORS 100

/*GLOBAL CONSTANTS*/
enum boolean{FALSE, TRUE};

/*GLOBAL VARIABLES*/
int perfectNumber;
int iterations;
int divisorList[100];


/*PROTOTYPES*/
void babSqrt(double, int);
void printChart(double,double, int, int);
int determineIfPerfectNumber(int candidate);

/*MAIN*/

int main(void){
	determineIfPerfectNumber(56);
	return 1;
}

/*SUBROUTINES*/

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

void babSqrt(double radicand, int decimalPrecision)
{
	const double PRECISION = 1 / pow(10, decimalPrecision);

	double runningSqrt,  //current iteration of square root
		   previousSqrt, //previous iteration of square root
		   error;        //difference between iterations
	int    squares,
		   counter;

	/*sets runningSqrt to an efficient first guess by finding the
	 * closest perfect square that is smaller than the radicand. */
	runningSqrt = 0.0;
	squares     = 0;
	while(squares < radicand)
	{
		previousSqrt = runningSqrt;
		runningSqrt++;
		squares = pow (runningSqrt, 2);
	}
	runningSqrt = previousSqrt;

	/*uses the babylonian method of squareroot calculation.
	 * loop ends when the difference between iterations is smaller
	 * than a certain error term */
	counter = 0;
	error = runningSqrt;
	while(error >  PRECISION)
	{
		previousSqrt = runningSqrt;
		runningSqrt  = 0.5 * (runningSqrt + (radicand / runningSqrt));
		error = fabs( runningSqrt - previousSqrt );
		counter++;
	}

	printChart(radicand, runningSqrt, decimalPrecision, counter);
}

/* ========================================================================
 * function: 
 *  purpose:
 *
 *  @params:
 *
 *  @return:
 * ======================================================================*/

int determineIfPerfectNumber(int candidate)
{
	const int MAX_DIVISORS = 100;

	int divisorList[MAX_DIVISORS],
		index,
		largestFactor,
		divisor,
		runningSum;

	for(index = 0; index < MAX_DIVISORS; index++)
	{
		divisorList[index] = 0;
	}

	divisor = 2;
	largestFactor = candidate;
	runningSum = 1;
	index = 1;
	divisorList[0] = 1;
	while((divisor < largestFactor) && (runningSum < candidate))
	{
		if(candidate % divisor == 0)
		{
			divisorList[index] = divisor;
			index++;
			largestFactor = candidate / divisor;
			divisorList[index] = largestFactor;
			index++;
			runningSum = runningSum + divisor + largestFactor;
		}
		
		divisor++;
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

int generatePerfectNumberCandidate(int input)
{
	return pow(2, input - 1) * (pow(2, input) - 1);
}

/* ========================================================================
 * function: 
 *  purpose:
 *
 *  @params:
 *
 *  @return:
 * ======================================================================*/

void printChart(double radicand, double runningSqrt,
		int decimalPrecision, int counter)
{
	printf("Perfect number : %.0f\n", radicand);
	printf("Expected sqrt() of %.0f = %.*f\n",
			radicand, decimalPrecision, sqrt(radicand)); 
	printf("Computed square root of %.0f = %.*f\n",
			radicand, decimalPrecision, runningSqrt);
	printf("reached in %d iterations\n", counter);
	putchar('\n');
}
