#include "matrix.h"

#include <stdlib.h>

void mat_set_all(t_mat *matrix, const MAT_TYPE *const arr[])
{
	size_t row_it;

	row_it = 0;
	while (row_it < matrix->num_rows)
	{
		mat_set_row(matrix, row_it + 1, arr[row_it]);
		row_it++;
	}
}

int mat_set_row(t_mat *matrix, const size_t row, const MAT_TYPE arr[])
{
	size_t col_it;

	if (row == 0)
		return (MAT_ERROR("ERROR Row cannot be 0"), MAT_RET_ERROR);
	if (row > matrix->num_rows)
		return (MAT_ERROR("ERROR Row cannot be more than theire are rows in matrix"), MAT_RET_ERROR);
	col_it = 0;
	while (col_it < matrix->num_cols)
	{
		matrix->data[((row - 1) * matrix->num_cols) + col_it] = arr[col_it];
		col_it++;
	}
	return (MAT_RET_OK);
}

int mat_set_col(t_mat *matrix, const size_t col, const MAT_TYPE arr[])
{
	size_t row_it;

	if (col == 0)
		return (MAT_ERROR("ERROR Column cannot be 0"), MAT_RET_ERROR);
	if (col > matrix->num_cols)
		return (MAT_ERROR("ERROR Row cannot be more than theire are rows in matrix"), MAT_RET_ERROR);
	row_it = 0;
	while (row_it < matrix->num_rows)
	{
		matrix->data[(row_it * matrix->num_cols) + (col - 1)] = arr[row_it];
		row_it++;
	}
	return (MAT_RET_OK);
}

void mat_fill_all(t_mat *matrix, const MAT_TYPE value)
{
	size_t i;
	
	i = 0;
	while (i < matrix->num_cols * matrix->num_rows)
	{
		matrix->data[i] = value;
		i++;
	}
}
