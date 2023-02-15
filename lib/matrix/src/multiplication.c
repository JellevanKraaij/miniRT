#include "matrix.h"

#include <math.h>

static MAT_TYPE m_dotproduct(const t_mat *row_matrix, const size_t row, const t_mat *col_matrix, const size_t col)
{
	size_t i;
	double ret;

	i = 0;
	ret = 0;
	while (i < row_matrix->num_cols)
	{
		ret += row_matrix->data[i + (row * row_matrix->num_cols)] * col_matrix->data[(i * col_matrix->num_cols) + col];
		i++;
	}
	return (ret);
}

t_mat *mat_multiply(const t_mat *lhs, const t_mat *rhs)
{
	t_mat	*ret;
	size_t	i;

	if (lhs->num_cols != rhs->num_rows || lhs->num_cols != rhs->num_rows)
	{
		MAT_ERROR("ERROR unable to multiple due to incorrect sizes");
		return (NULL);
	}
	ret = mat_new(lhs->num_rows, rhs->num_cols);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < ret->num_rows * ret->num_cols)
	{
		ret->data[i] = m_dotproduct(lhs, i / lhs->num_rows, rhs, i % rhs->num_cols);
		i++;
	}
	return (ret);
}

int mat_multiply_assign(t_mat *lhs, const t_mat *rhs)
{
	t_mat	*tmp;
	size_t	i;

	if (lhs->num_cols != rhs->num_rows || lhs->num_cols != rhs->num_rows)
	{
		MAT_ERROR("ERROR unable to multiple due to incorrect sizes");
		return (MAT_RET_ERROR);
	}
	tmp = mat_new(lhs->num_rows, rhs->num_cols);
	if (tmp == NULL)
		return (MAT_RET_ERROR);
	i = 0;
	while (i < tmp->num_rows * tmp->num_cols)
	{
		tmp->data[i] = m_dotproduct(lhs, i / lhs->num_rows, rhs, i % rhs->num_cols);
		i++;
	}
	mat_cpy(lhs, tmp);
	mat_free(tmp);
	return (MAT_RET_OK);
}

t_mat *mat_multiply_scalar(const t_mat *lhs, MAT_TYPE rhs)
{
	t_mat *ret;
	size_t i;

	ret = mat_dup(lhs);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while(i < ret->num_rows * ret->num_cols)
	{
		ret->data[i] *= rhs;
		i++;
	}
	return (ret);
}

int mat_multiply_scalar_assign(t_mat *lhs, MAT_TYPE rhs)
{
	size_t i;

	i = 0;
	while(i < lhs->num_rows * lhs->num_cols)
	{
		lhs->data[i] *= rhs;
		i++;
	}
	return (MAT_RET_OK);
}
