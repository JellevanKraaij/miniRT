#include "matrix3d.h"


t_vec3 *mat_is_vec3(t_mat *matrix)
{
	if (matrix->num_rows != 1 || matrix->num_cols != 3)
		return (NULL);
	return (matrix);
}

t_mat3 *mat_is_mat3(t_mat *matrix)
{
	if (matrix->num_rows != 3 || matrix->num_cols != 3)
		return (NULL);
	return (matrix);
}
