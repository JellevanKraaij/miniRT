#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef	MAT_TYPE
# define MAT_TYPE double
#endif

void mat_error(const char *error);

#ifndef MAT_ERROR
# define MAT_ERROR(x) mat_error(x)
#endif

#define MAT_RET_ERROR	-1
#define MAT_RET_OK		0

typedef struct s_mat
{
	size_t num_rows;
	size_t num_cols;

	MAT_TYPE *data;
}	t_mat;

t_mat	*mat_new(const size_t num_rows, const size_t num_cols);

t_mat	*mat_dup(const t_mat *matrix);

t_mat 	*mat_cpy(t_mat *dst, const t_mat *src);

void	mat_fill_all(t_mat *matrix, const MAT_TYPE value);

void	mat_set_all(t_mat *matrix, const MAT_TYPE *const *arr);
int		mat_set_row(t_mat *matrix, const size_t row, const MAT_TYPE *arr);
int		mat_set_col(t_mat *matrix, const size_t col, const MAT_TYPE *arr);

bool	mat_eq_dm(const t_mat *lhs, const t_mat *rhs);

t_mat	*mat_add(const t_mat *lhs, const t_mat *rhs);
t_mat	*mat_subtract(const t_mat *lhs, const t_mat *rhs);
t_mat	*mat_multiply(const t_mat *lhs, const t_mat *rhs);
t_mat	*mat_multiply_scalar(const t_mat *lhs, MAT_TYPE rhs);

int		mat_add_assign(t_mat *lhs, const t_mat *rhs);
int		mat_subtract_assign(t_mat *lhs, const t_mat *rhs);
int		mat_multiply_assign(t_mat *lhs, const t_mat *rhs);
int		mat_multiply_scalar_assign(t_mat *lhs, MAT_TYPE rhs);

void 	mat_print(const t_mat *matrix);

void	mat_free(t_mat *matrix);

#endif

5 + 6
