#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

static t_mat *mat_alloc(void)
{
	t_mat *ret;

	ret = malloc(sizeof(t_mat));
	if (ret == NULL)
		MAT_ERROR("ERROR Allocation");
	return (ret);
}

static MAT_TYPE *mat_data_alloc(const size_t num_rows, const size_t num_cols)
{
	MAT_TYPE *ret;

	ret = malloc(sizeof(MAT_TYPE) * num_rows * num_cols);
	if (ret == NULL)
		MAT_ERROR("Allocation ERROR");
	return (ret);
}

t_mat *mat_new(const size_t num_rows, const size_t num_cols)
{
	t_mat *ret;

	if (num_rows == 0 || num_cols == 0)
	{
		MAT_ERROR("ERROR Rows/cols cannot be 0");
		return (NULL);
	}
	ret = mat_alloc();
	if (ret == NULL)
		return (NULL);
	ret->num_rows = num_rows;
	ret->num_cols = num_cols;
	ret->data = mat_data_alloc(num_rows, num_cols);
	if (ret->data == NULL)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_mat *mat_dup(const t_mat *matrix)
{
	t_mat *ret;

	ret = mat_new(matrix->num_rows, matrix->num_cols);
	if (ret == NULL)
		return (NULL);
	return (mat_cpy(ret, matrix));
}

void mat_free(t_mat *matrix)
{
	free(matrix->data);
	free(matrix);
}
