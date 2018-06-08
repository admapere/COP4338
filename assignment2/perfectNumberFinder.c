/* ========================================================================
 * Source Code: perfectNumberFinder.c
 *      Author: Adrian Manuel Perez
 *  Student ID: 3180957
 *  Assignment: Program #2 - Perfect Number Finder
 *  
 *      Course: COP 4338 (Advanced Programming)
 *     Section: U01
 *  Instructor: William Feild
 *    Due Date: 08 February, 2018 beginning of class
 *  
 * I hereby certify that this collective work is my own
 * and none of it is the work of any other person or entity.
 * ______________________________________________[Signature]
 *
 *    Language: c
 * Compile/Run: gcc perfectNumberFinder.c -o perfectNumberFinder.out -lm
 *              ./perfectNumberFinder.out
 * +----------------------------------------------------------------------
 *
 * Description: Print out all the perfect numbers in a given range
 *       Input: none
 *      Output: prints out the following the perfect number along with
 *              the sum of the sequence of divisors of the number
 *              and then it prints out the square root, both using the
 *              babylonian method and the method provided by the <math.h>
 *
 *     Process: + Loops through every value in the interval [MIN,MAX]
 *              + Creates a list of factors for every value.
 *              + Finds the Aliquot sum of the list (sum of every factor,
 *                except the last) https://en.wikipedia.org/wiki/Aliquot_sum
 *              + Determines if the sum is equal to the candidate value
 *                  + If it is, print out the sum and the squareroot
 *                  + Else, do nothing
 *              + Repeat loop until reaching the end.
 *
 * Missing Features: none
 *       Known Bugs: text doesn't wrap nicely in smaller windows
 * ======================================================================*/

/*INCLUDES*/
#include <stdio.h>  
#include <math.h>   //sqrt()

/*DEFINES*/
#define MIN_INTERVAL 1
#define MAX_INTERVAL 10000
#define DESIRED_PRECISION 16

/*PROTOTYPES*/
int    aliquotSum(int*);
void   babSqrt(double, int);
int*   createFactorList(int);
int    determineInitialGuess(double);
void   printChart(double,double, int, int);
void   printSum(int, int*);
/*MAIN*/

int main(void)
{
    int  perfectNumberCandidate;
    int  sum;
    int* factorList;

    /*Loops through every value in the interval and checks if they are
     *perfect numbers. If they are, print out the charts, otherwise break */
    perfectNumberCandidate = MIN_INTERVAL;
    while(perfectNumberCandidate < MAX_INTERVAL)
    {
        factorList = createFactorList(perfectNumberCandidate);
        sum = aliquotSum(factorList);

        if(sum == perfectNumberCandidate)
        {
            printSum(perfectNumberCandidate, factorList);
            babSqrt(perfectNumberCandidate, DESIRED_PRECISION);
        }

        perfectNumberCandidate++;
    }

    return 1;
}

/*SUBROUTINES*/
/* ========================================================================
 * function: aliquotSum
 *  purpose: sum every number in a given array and divide by 2
 *
 *  @params: factorList pointer to a list of factors
 *
 *  @return: sum the sum of the factor list
 * ======================================================================*/

int aliquotSum(int factorList[])
{
    int index;
    int sum;

    /*the factor list shouldn't have negative numbers, so the first
     * negative number tells us the list of factors is over
     * thus, the loop ends when it encounters a negative number*/
    sum = 0;
    for(index = 0 ; factorList[index] > -1 ; index++)
    {
        sum += factorList[index];
    }
    sum = sum / 2;
    return sum;
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

void babSqrt(double radicand, int decimalPrecision)
{   
    const double PRECISION = 1 / pow(10, decimalPrecision);

    long double runningSqrt;  //current iteration of square root
    long double previousSqrt; //previous iteration of square root
    long double error;        //difference between iterations
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
 * function: determineInitialGuess
 *  purpose: helper method for the babSqrt. It determines an efficient
 *           first guess.
 *
 *  @params: radicand the number to find the square root
 *
 *  @return: previousGuess the best guess of the square root
 * ======================================================================*/

int determineInitialGuess(double radicand){
    #define INITIAL_GUESS 1

    int runningGuess;
    int previousGuess;
    int square;

    /*finds the closest perfect square to the radicand*/
    runningGuess  = INITIAL_GUESS;
    previousGuess = runningGuess - 1;
    square        = runningGuess;
    while ( square <= radicand )
    {
        previousGuess = runningGuess;
        runningGuess++;

        square = pow ( runningGuess, 2 );
    }

    return previousGuess;
}
/* ========================================================================
 * function: createFactorList
 *  purpose: creates a list of factors of a given number
 *
 *  @params: candidate candidate for a perfect number
 *
 *  @return: factorList pointer to a list of factors of perfect number
 * ======================================================================*/

int* createFactorList(int candidate)
{
    #define MAX_DIVISORS 1000
    static int factorList [ MAX_DIVISORS ];

    int smallerIndex;
    int largerIndex;
    int smallerFactor;
    int largerFactor;

    /*Divides the candidate number, creating a table of factors such that
     *the smaller factors are on the left and the larger factors are on
     *the right*/   
    smallerFactor = 1;
    largerFactor  = candidate;
    smallerIndex  = 0;
    largerIndex   = MAX_DIVISORS - 1;
    while(smallerFactor < largerFactor)
    {
        if(candidate % smallerFactor == 0)
        {
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
    if(factorList[smallerIndex -1 ]  == factorList[largerIndex])
    {
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
 * function: printChart
 *  purpose: helper method that prints the information produced by the 
 *           babSqrt method
 *
 *  @params: radicand         the number to be square rooted
 *           squareRoot       the number computed by the babSqrt function
 *           decimalPrecision how precise a square root is 
 *           counter          number of iterations to find the square root
 *
 *  @return: void
 * ======================================================================*/

void printChart(double radicand, double squareRoot,
        int decimalPrecision, int counter)
{
    printf("%s %-10.0f %s %.*f\n","Expected square root of",radicand,"=",
            decimalPrecision, sqrt(radicand)); 
    printf("%s %-10.0f %s %.*f\n","Computed square root of",radicand,"=",
            decimalPrecision, squareRoot);
    printf("%s %d %s\n","reached in", counter,"iterations");
}
/* ========================================================================
 * function: printSum
 *  purpose: helper method that prints a perfectNumber as well as the sum
 *           of its factors
 *
 *  @params: perfectNumber the perfect number to which the factors belong
 *           factorList    pointer to the list of factors of the number
 *
 *  @return: void
 * ======================================================================*/

void printSum(int perfectNumber, int *factorList)
{
    printf("\n%s %d %s","Perfect number:",perfectNumber,"= 1");
    int index = 1;
    for(index; factorList[index] != perfectNumber; index++)
    {
        printf(" %s %d","+", factorList[index]);
    }
    putchar('\n');
}
