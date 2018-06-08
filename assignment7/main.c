#include "matrix.h"

int main(int argc, char **argv){
	struct matrix a;
	char buf[BUFSIZ];
	unsigned int i;

	srand(time(NULL));
	
	a.nrow = strtol(*(argv + 1), NULL, 10);
	a.ncol = strtol(*(argv + 2), NULL, 10);
	a.arr = (double *)malloc(a.ncol * a.nrow * sizeof(a.arr));
	
	for (i = 0; i < a.nrow * a.ncol; i++){
		*(a.arr + i) = (double)rand() / RAND_MAX;
	}
	mat_to_str(buf, &a, a.nrow * a.ncol);
	printf("%s\n", buf);
	
	free(a.arr);
	return EXIT_SUCCESS;
}
