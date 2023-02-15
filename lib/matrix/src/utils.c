#include "matrix.h"

bool mat_eq_dm(const t_mat *lhs, const t_mat *rhs)
{
	return ((lhs->num_cols == rhs->num_cols) && (lhs->num_rows == rhs->num_rows));

}

t_mat *mat_cpy(t_mat *dst, const t_mat *src)
{
	size_t i;

	i = 0;
	if (!mat_eq_dm(dst, src))
	{
		MAT_ERROR("ERROR Matrix not same size");
		return (NULL);
	}
	while (i < dst->num_cols * dst->num_rows)
	{
		dst->data[i] = src->data[i];
		i++;
	}
	return (dst);
}
