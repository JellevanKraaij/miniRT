#include "matrix3d.h"
#include <math.h>

MAT_TYPE mat_vec3_dot(const t_vec3 *vec1, const t_vec3 *vec2)
{
	size_t i;
	double ret;

	if (!mat_is_vec3(vec1) || !mat_is_vec3(vec2))
	{
		return (MAT_ERROR("ERROR matrix is not of type vec3"), NAN);
	}
	i = 0;
	ret = 0;
	while (i < vec1->num_rows * vec1->num_cols)
	{
		ret += vec1->data[i] * vec2->data[i];
		i++;
	}
	return (ret);
}
