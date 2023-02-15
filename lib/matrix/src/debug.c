#include "matrix.h"

#include <stdio.h>

void mat_error(const char *error)
{
	fprintf(stderr, "%s\n", error);
	exit(1);
}

void mat_print(const t_mat *matrix)
{
	size_t row_it;
	size_t col_it;

	row_it = 0;
	while (row_it < matrix->num_rows)
	{
		col_it = 0;
		while (col_it < matrix->num_cols)
		{
			printf("%lf ", matrix->data[(row_it * matrix->num_cols) + col_it]);
			col_it++;
		}
		printf("\n");
		row_it++;
	}	
}
