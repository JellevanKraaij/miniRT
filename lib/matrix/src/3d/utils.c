#include "matrix3d.h"

bool mat_is_vec3(const t_mat *matrix)
{
	if (matrix->num_rows != 1 || matrix->num_cols != 3)
		return (false);
	return (true);
}

bool mat_is_mat3(const t_mat *matrix)
{
	if (matrix->num_rows != 3 || matrix->num_cols != 3)
		return (false);
	return (true);
}

int mat_vec3_set(t_vec3 *vec, const MAT_TYPE arr[])
{
	if (!mat_is_vec3(vec))
		return (MAT_ERROR("ERROR matrix is not of type vec3"), MAT_RET_ERROR);
	mat_set_row(vec, 1, arr);
	return (MAT_RET_OK);
}
