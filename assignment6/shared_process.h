/*
 * Source Code: shared_process.h
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
#ifndef SHARED_PROCESS_H
#define SHARED_PROCESS_H

#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h> //strtol 
#include <string.h> //strlen
#include <math.h>   //pow
#include <errno.h>  //errno

#include <sys/shm.h>//shmat, shmdt, shmctl, shmget
#include <sys/wait.h> //wait

#include <unistd.h> //fork

#define	ARGC_MIN 2
#define	ARGC_MAX 8
#define	ARGV_MIN 0
#define	ARGV_MAX 9
#define arrlen(arr) (sizeof(arr)/sizeof(arr[0]))

int obtain_memory(int **shm_ptr, int n_elem);
void init_memory(int *shm_ptr, const int *data, int n_elem);
int create_children(pid_t *children_id, int nchild);

void child_process(int *shm_ptr ,int child_ID, int nchild);
void parent_process(const int *shm_ptr, const int *children_id, 
		    int shm_id, int nchild);

int arr_to_string(char *buf, const int *src, int n_elem);
int find_pid(const pid_t *children_pid, int nchild, pid_t child_pid);
int validate_inputs(int argc, const char *argv[], int *nchild, int data[]);

#endif /*SHARED_PROCESS_H*/
