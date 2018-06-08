#include "matrix.h"

void add(const struct matrix *a, const struct matrix *b,
		struct matrix *c)
{

}

void subtract(const struct matrix *a, const struct matrix *b,
		struct matrix *c)
{

}

int mat_to_str(char *buf, const struct matrix *mat, size_t nelems)
{
#define COL_WIDTH 4
	char *iter = buf;
	unsigned int i, j;
	double *arr;
	size_t nrow, ncol;

	arr = mat->arr;
	nrow = mat->nrow;
	ncol = mat->ncol;

	for (i = 0; i < nrow; i++){
		iter += sprintf(iter, "%c", '[');
		for (j = 0; j < ncol; j++){
			iter += sprintf(iter, "%*.2f",
					(j == 0) ? COL_WIDTH: COL_WIDTH + 1,
					*(arr + j + (i * ncol)));
		}
		iter += sprintf(iter, "%c\n", ']');
	}
	return buf - iter;
#undef COL_WIDTH
}
