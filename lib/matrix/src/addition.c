#include <matrix.h>

t_mat *mat_add(const t_mat *lhs, const t_mat *rhs)
{
	t_mat	*ret;
	size_t	i;

	if (!mat_eq_dm(lhs, rhs))
	{
		MAT_ERROR("ERROR Matrix not same size");
		return (NULL);
	}
	ret = mat_new(lhs->num_rows, lhs->num_cols);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < ret->num_cols * ret->num_rows)
	{
		ret->data[i] = lhs->data[i] + rhs->data[i];
		i++;
	}
	return (ret);
}

int mat_add_assign(t_mat *lhs, const t_mat *rhs)
{
	size_t	i;

	if (!mat_eq_dm(lhs, rhs))
	{
		MAT_ERROR("ERROR Matrix not same size");
		return (MAT_RET_ERROR);
	}
	i = 0;
	while (i < lhs->num_cols * lhs->num_rows)
	{
		lhs->data[i] += rhs->data[i];
		i++;
	}

	return (MAT_RET_OK);
}