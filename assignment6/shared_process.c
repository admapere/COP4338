/*
 * Source Code: shared_process.c
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
 */

#include "shared_process.h"

/*
 * obtain_memory
 * 
 * Gets and then attaches shared memory to the calling process.
 *
 * @params int **shm_ptr  the shared memory pointer to be assigned
 * @params int n_elements number of elements to store
 * @return                the shared memory ID
 */
int obtain_memory(int **shm_ptr, int n_elem){
	const int intsize = sizeof(n_elem);
	int shm_id = 0;

	shm_id = shmget(IPC_PRIVATE, n_elem * intsize, IPC_CREAT | 0666);
	if (shm_id == -1){
		perror("ERROR");
		exit(EXIT_FAILURE);
	}//end if

	printf("Parent: Getting %d bytes of shared memory\n",
		n_elem * intsize);

	*shm_ptr = (int *) shmat(shm_id, NULL, 0);
	if (*(long *)shm_ptr == -1){
		perror("ERROR");
		exit(EXIT_FAILURE);
	}//end if

	printf("Parent: Attaching %d bytes of shared memory at 0x%X\n", 
		n_elem * intsize, *shm_ptr);
	
	return shm_id;
}//end function
/*
 * init_memory
 * 
 * Initializes n_elem amount of 'shm_ptr' with data found at 'data'. 
 * Prints a trace statement.
 *
 * @params int *shm_ptr pointer to shared memory destination
 * @params int *data    point to source for the shared memory
 * @params int n_elem   the length of data
 */
void init_memory(int *shm_ptr, const int *data, int n_elem){
	const int intsize = sizeof(n_elem);
	char buf[n_elem * intsize];

	arr_to_string(buf, shm_ptr, n_elem);
	printf("Parent: shared memory contains: %s\n", buf);
	
	arr_to_string(buf, data, n_elem);
	printf("Parent: argv[] contains: %s\n", buf);

	memcpy(shm_ptr, data, n_elem * intsize);
	printf("%s\n", "Parent: copying data from argv[] to shared memory");
	
	arr_to_string(buf, shm_ptr, n_elem);
	printf("Parent: shared memory contains: %s\n\n", buf);
}//end function
/* 
 * create_children
 *
 * Creates number of children equal to the nchild paramater. It then sets
 * child and parent's pid. A trace statement is printed each time a child is
 * born.
 *
 * @params pid_t *children_id the process id of the individual child to be 
 *			      modified
 * @params int nchild  the number of processes to spawn
 *
 * @return int child_id number representing the order in which the children
 *                      were created. If the number is 0, it indicates that
 *                      it is the parent.
 */
int create_children(pid_t *children_id, int nchild){
	int index = 0;
	int child_id = 0;
	int status = 0;
	pid_t f_pid = 1;
	
	for (index = 0; (index < nchild) && (f_pid != 0); index++){
		printf("Parent: Creating child %d\n", index + 1);
		fflush(stdout);
		f_pid = (pid_t) fork();

		*(children_id + index) = f_pid;
		child_id = index + 1;
	}//end for

	if(f_pid < 0){
		perror("ERROR:");
		exit(EXIT_FAILURE);
	}//end if
	
	if (f_pid > 0){
		child_id = 0;
	}//end if
	
	return child_id;
}//end function
/*
 * child_process
 *
 * Gets the child's id and multiplies it by the corresponding element in the
 * shared memory. It then stores the product in the shared 
 * memory.
 *
 * Trace statements are provided throughout.
 *
 * @params int *shm_ptr pointer to the shared memory between all processes.
 * @params int child_id the id assigned by the parent to the child.
 * @params int nchild   the number of children to be processed
 */
void child_process(int *shm_ptr, int child_id, int nchild){
	//Child id is an ordinal number, therefore the 1st child corresponds
	//to the 0th element
	const char *multiply_symbol = "\u00D7";
	char arr_str[nchild * sizeof(nchild)];
	char buf[BUFSIZ];
	char *buf_ptr = buf;
	int factor_1 = child_id;
	int factor_2 = *(shm_ptr + child_id - 1);
	int product = factor_1 * factor_2;
	
	arr_to_string(arr_str, shm_ptr, nchild);
	buf_ptr += (char) sprintf(buf_ptr,
		"\tChild %d: Status of shared memory at 0x%X %s\n",
		child_id, shm_ptr, arr_str);

	buf_ptr += (char) sprintf(buf_ptr,
		"\tChild %d: My unique ID is %d\n",
		child_id, child_id);

	buf_ptr += (char) sprintf(buf_ptr,
		"\tChild %d: %d %s %d = %d\n",
		child_id, factor_1, multiply_symbol, factor_2, product);
	
	*(shm_ptr + child_id - 1) = product;
	
	arr_to_string(arr_str, shm_ptr, nchild);
	buf_ptr += (char) sprintf(buf_ptr,
		"\tChild %d: Shared memory at 0x%X contains %s\n",
		child_id, shm_ptr, arr_str);

	printf("%s\n", buf);
}//end function
/*
 * parent_process
 *
 * Waits for all it's children to finish. When one of the children finishes
 * prints a trace statement stating that the parent knows it is done. After
 * children finish their processes, the parent prints out the status of the
 * shared memory, detatches, and removes the memory.
 *
 * @params int *shm_ptr           pointer to the shared memory
 * @params const int *children_id pointer to children_id array
 * @params int shm_id		  id to the shared memory
 * @params int nchild		  number of children in array
 */
void parent_process(const int *shm_ptr, const int *children_id,
		    int shm_ID, int nchild) {

	char buf[BUFSIZ] = {'\0'};
	char *buf_ptr = buf;
	char arr_str[nchild * sizeof(nchild)];
	int index = 0;
	int child_id = 0;
	int *child_id_ptr = NULL;
	int status[nchild];
	pid_t child_pid = 0;
	
	for (index = 0; index < nchild; index++){
		buf_ptr += (char) sprintf(buf_ptr,"%s\n",
			"Parent: Waiting for children");

		/*determines if children ended and finds which one ended*/
		child_pid = wait(&status[index]);
		child_id = find_pid(children_id, nchild, child_pid);

		buf_ptr += (char) sprintf(buf_ptr,
			"Parent: Child %d has ended their process\n",
			child_id);
		buf_ptr += (char) sprintf(buf_ptr,
			"Parent: Child %d exit code is %d\n\n",
			child_id, status[index]);
	}//end for
	
	buf_ptr += (char) sprintf(buf_ptr, "%s\n",
		"Parent: All children have ended their processes");

	arr_to_string(arr_str, shm_ptr, nchild);
	buf_ptr += (char) sprintf(buf_ptr, 
		"Parent: The shared memory now contains %s\n", arr_str);

	buf_ptr += (char) sprintf(buf_ptr, 
		"Parent: Detaching shared memory at 0x%X\n", shm_ptr);
	buf_ptr += (char) sprintf(buf_ptr,
		"Parent: Free shared memory at 0x%X\n", shm_ptr);

	shmdt(shm_ptr);
	shmctl(shm_ID, IPC_RMID, NULL);
	printf("%s\n", buf);
}//end function
/*
 * arr_to_string
 *
 * prints a string representation of the source array to a destination
 * buffer. The string looks like [a0, a1, a2, ..., an]
 *
 * @params char *buf  buffer to be printed to
 * @params int *src   buffer to be printed from
 * @params int n_elem number of elements to print
 *
 * @return number of characters correctly printed
 */
int arr_to_string(char *buf, const int *src, int n_elem){
	const char *buf_start = buf;
	int index = 0;

	*buf = '[';
	for (index = 0; index < n_elem; index++){
		buf++;
		buf += sprintf(buf, "%d", *(src + index));
		*buf = ',';
	}//end for
	*buf = ']';
	buf++;
	*buf = '\0';

	return buf - buf_start;
}//end function
/*
 * find_pid
 * 
 * finds a pid and returns it's relative position
 *
 * @params const pid_t *children_pid array of children pids
 * @params int nchild                length of array
 * @params pid_t child_pid           pid to be compared
 *
 * @return
 */
int find_pid(const pid_t *children_pid, int nchild, pid_t child_pid){
	int index = 0;

	for (index = 0; index < nchild; index++){
		if (*(children_pid + index) == child_pid){
			return index + 1;
		}//end if
	}//end for
	return -1;
}//end function
/*
 *  validate_inputs
 *  
 *  Function is divided into three general areas. First, the function
 *  determines if there are too many or too few arguments by checking
 *  against ARGC_MAX and ARGC_MIN
 *
 *  Next, it parses each argv entry by entry. If argv is not a number
 *  the program exits and says it was expecting an integer in ARGV_MIN,
 *  ARGV_MAX
 *
 *  Finally, it checks if the inputs are duplicates. It does so by using a
 *  bit field to check which numbers have already been chosen. This was used
 *  for it's constant time complexity.
 *
 *  @params argc    number of command line inputs
 *  @params *argv[] pointer to array of command line args
 *  @params *nchild pointer to number of children to make
 *  @params data[]  array of childID 
 *  @return	    number of correctly verified inputs
 */
int validate_inputs(int argc, const char *argv[], int *nchild, int data[]){
	#define NUM_BASE 10

	/*verify number of command line inputs*/
	if (argc > ARGC_MAX){
		fprintf(stderr,
			"ERROR: too many args expected less than %d\n",
			ARGC_MAX);
		
		return EXIT_FAILURE;
	}//end if
	if (argc < ARGC_MIN){
		fprintf(stderr,
			"ERROR: too few args , expected %d or more\n",
			ARGC_MIN);

		return EXIT_FAILURE;
	}//end if

	*nchild = argc - 1;

	/* parse and validate, check bounds, and duplicates*/
	char *endptr = NULL;
	int prev_bit_field = 0;
	int bit_field = 0;
	int bit_mask = 0;
	int index = 0;
	int ID = 0;
	
	/*Index starts at 1 because argv[0] is the name of the program*/
	for (index = 1; index < argc; index++){
		errno = 0;
		ID = strtol(argv[index], &endptr, NUM_BASE);

		/*check argv validity*/
		if (*(argv[index]) == '\0' || *endptr != '\0' ){
			fprintf(stderr,
				"ERROR: '%s' not valid, need [%d,%d]\n",
				argv[index], ARGV_MIN, ARGV_MAX);
			
			return EXIT_FAILURE;
		}//end if

		/*check argv bounds*/
		if (errno != 0 || ID < ARGV_MIN || ID > ARGV_MAX){
			fprintf(stderr,
				"ERROR: '%s' out of bounds, need [%d,%d]\n",
				argv[index], ARGV_MIN, ARGV_MAX);
			
			return EXIT_FAILURE;
		}//end if

		/*check for duplicates*/
		/*bit field to determine which numbers have been picked*/
		prev_bit_field = bit_field;
		bit_mask = pow(2, ID);
		bit_field |= bit_mask;

		if (bit_field == prev_bit_field){
			fprintf(stderr, "ERROR: '%s' is a duplicate\n",
				argv[index]);

			return EXIT_FAILURE;
		}//end if

		data[index - 1] = ID;
	}//end for

	return EXIT_SUCCESS;
	#undef NUM_BASE
}//end function
