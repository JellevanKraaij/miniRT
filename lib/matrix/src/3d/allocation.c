#include "matrix3d.h"

t_vec3	*mat_vec3_new(void)
{
	return (mat_new(1, 3));
}

t_mat3	*mat_mat3_new(void)
{
	return (mat_new(3, 3));
}

t_mat3 *mat_vec3_new_set(const MAT_TYPE *arr)
{
	t_mat3 *ret;

	ret = mat_vec3_new();
	if (ret == NULL)
		return (NULL);
	mat_vec3_set(ret, arr);
	return (ret);
}
