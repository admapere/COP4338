#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h> /*malloc, free*/
#include <string.h> /*strtol*/
#include <errno.h>
#include <time.h> /*time*/

#include <pthread.h> 

struct matrix {
	size_t nrow, ncol;
	double *arr;
};

void add(const struct matrix *, const  struct matrix *,
	struct matrix *);
void subtract(const struct matrix *, const struct matrix *, 
	struct matrix *);

int mat_to_str(char *, const struct matrix *, size_t);

#endif
