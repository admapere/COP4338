/*
 * Source Code: main_shared_process.c
 *      Author: Adrian Manuel Perez
 *  Student ID: 3180957
 *  Assignment: Assigment 6 Shared Processes
 * 
 *      Course: COP 4338 Advanced Programming
 *     Section: U01
 *  Instructor: William Feild
 *    Due Date: 19 April 2018, 6:25
 *
 *              I hereby certify that this collective work is my own
 *              and none of it is the work of any other person or entity.
 *              _____________________________________________[Signature]
 *
 *    Language: C
 * Compile/Run: 
 *      $ make build
 *      $ ./test_shared_process.out [command line arguments]
 *      OR
 *      $ gcc -std=c99 -lm -o test_shared_process.out 
 *        main_shared_process.c shared_process.c
 *      $ ./test_shared_process.out [command line arguments]
 *
 * +--------------------------------------------------------------------
 *
 * Description: Program's purpose is to get numeric input from the user
 *		and multiply it by it's relative position, and print
 *		the values that it does. To do the mathematics, the program
 *		will fork children equal to the number of inputs to do
 *		the various calculations
 *
 *       Input: Up to ARGC_MAX - 1 integers in [ARG_MIN, ARG_MAX]
 *      Output: The array that was calculated, along with all the trace
 *		statements of each child and parent doing the calculations
 *
 *     Process: Program does the following:
 *		1. Process input from user
 *		2. Request and attach shared memory from OS
 *		3. Fork off enough children to do calculations in parallel
 *		4. Return control to parent
 *		5. Detach and free memory from OS
 *
 * Missing Features:
 *       Known Bugs:
 */

#include "shared_process.h"

int main(int argc, const char *argv[]){
	int nchild = 0, shm_id = 0, child_id = 0;
	int data[ARGC_MAX - 1] = {0};
	int *shm_ptr = NULL;

	pid_t children_pid[ARGC_MAX - 1] = {0};

	validate_inputs(argc, argv, &nchild, data);

	shm_id = obtain_memory(&shm_ptr, nchild);
	init_memory(shm_ptr, data, nchild);
	child_id = create_children(children_pid, nchild);
	
	if (child_id > 0){
		child_process(shm_ptr, child_id, nchild);
	}//end if
	if (child_id == 0){
		parent_process(shm_ptr, children_pid, shm_id, nchild);
	}//end if
	
	return EXIT_SUCCESS;
}
