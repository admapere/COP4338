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
#define DESIRED_PRECISION 16

/*GLOBAL CONSTANTS*/
enum boolean{FALSE, TRUE};

/*PROTOTYPES*/
int    aliquotSum(int*);
void   babSqrt(double, int);
int    determineInitialGuess(double);
int    euclidEulerFormula(int);
int*   createDivisorList(int);
void   printChart(double,double, int, int);
void   printSum(int, int*);
/*MAIN*/

int main(void)
{
	int perfectNumberCandidate,
	    index,
		*array,
		sum;
	
	index = 1;
	perfectNumberCandidate = euclidEulerFormula(index);
	while(perfectNumberCandidate < MAX_INTERVAL)
	{
		array = createDivisorList(perfectNumberCandidate);
		sum = aliquotSum(array);

		if(sum == perfectNumberCandidate)
		{
			printSum(perfectNumberCandidate, array);
			babSqrt(perfectNumberCandidate, DESIRED_PRECISION);
		}
	
	index++;
	perfectNumberCandidate = euclidEulerFormula(index);
	}

	return 1;
}

/*SUBROUTINES*/

/* ========================================================================
 * function: 
 *  purpose:
 *
 *  @params:
 *
 *  @return:
 * ======================================================================*/

int aliquotSum(int divisorList[]){
	int index,
	    sum;

	sum = 0;
	for(index = 0 ; divisorList[index] > -1 ; index++){
		sum += divisorList[index];
	}
	sum = sum / 2;
	return sum;
}

/* ========================================================================
 * function: babSqrt 
 *  purpose: calculates the square root of a number recursively using the
 *           babylonian method:
 i*           let X be an initial guess
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
	
	long double runningSqrt,  //current iteration of square root
		        previousSqrt, //previous iteration of square root
		        error;        //difference between iterations
	int         counter;      //counts iterations

	/*uses the babylonian method of squareroot calculation.
	 *loop ends when the difference between iterations is smaller
	 *than a certain error term*/
	counter = 0;
	runningSqrt = determineInitialGuess(radicand);
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

int determineInitialGuess(double radicand){
	const int INITIAL_GUESS = 1;
	
	int     runningGuess,
	        previousGuess,
	        square;

	runningGuess  = INITIAL_GUESS;
	previousGuess = runningGuess - 1;
	square        = runningGuess;
	while ( square <= radicand ){
		previousGuess = runningGuess;
		runningGuess++;

		square = pow ( runningGuess, 2 );
	}

	return previousGuess;
}
/* ========================================================================
 * function: 
 *  purpose:
 *
 *  @params:
 *
 *  @return:
 * ======================================================================*/

int* createDivisorList(int candidate){
	#define MAX_DIVISORS 100
	static int factorList [ MAX_DIVISORS ];
	
	int	smallerIndex, largerIndex,
		smallerFactor, largerFactor;

	/*Divides the candidate number, creating a table of factors such that
	 *the smaller factors are on the left and the larger factors are on
	 *the right*/	
	smallerFactor = 1;
	largerFactor  = candidate;
	smallerIndex  = 0;
	largerIndex   = MAX_DIVISORS - 1;
	while(smallerFactor < largerFactor){
		if(candidate % smallerFactor == 0){
			largerFactor = candidate / smallerFactor;

			factorList [ smallerIndex ] = smallerFactor;
			factorList [ largerIndex ]  = largerFactor;
			smallerIndex++;
			largerIndex--;
		}
		smallerFactor++;
	}
	/*Since the array produced above creates a list of integers
	 * to the left and to the right with empty values inbetween
	 * i.e. {1, 2, 4, 7, ..., 7, 14, 28}
	 * the following code moves the values on the right
	 * to the left, getting rid of any duplicates and ending the
	 * array with a -1, a value that should not appear, signalling
	 * the end of the factorlist 
	 * i.e. {1, 2, 4, 7, 14, 28, -1, ...}*/

	largerIndex++;        //Sets larger index into the correct position
	if(factorList[smallerIndex]  == factorList[largerIndex]){
		largerIndex++;    //this skips any duplicates
	}

	for (smallerIndex,largerIndex; largerIndex < MAX_DIVISORS ;
	    smallerIndex++, largerIndex++)
	{
		factorList [ smallerIndex ] = factorList [ largerIndex ];
	}
	factorList[ smallerIndex ] = -1;
	
	return factorList;	
}


/* ========================================================================
 * function: 
 *  purpose:
 *
 *  @params:
 *
 *  @return:
 * ======================================================================*/

int euclidEulerFormula(int input){
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
	printf("%s %-10.0f %s %.*f\n","Expected square root of",radicand,"=",
			decimalPrecision, sqrt(radicand)); 
	printf("%s %-10.0f %s %.*f\n","Computed square root of",radicand,"=",
			decimalPrecision, runningSqrt);
	printf("%s %d %s\n\n","reached in", counter,"iterations");
}

/* ========================================================================
 * function: 
 *  purpose:
 *
 *  @params:
 *
 *  @return:
 * ======================================================================*/

void printSum(int perfectNumber, int *factorList)
{
	printf("%s %d %s","Perfect number:",perfectNumber,"= 1");
	int index = 1;
	for(index; factorList[index] != perfectNumber; index++)
	{
		printf(" %s %d","+", factorList[index]);
	}
	putchar('\n');
}
