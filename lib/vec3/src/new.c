#include "vec3.h"

t_vec3	vec3_new(const VEC3_TYPE data[3])
{
	t_vec3 ret;

	vec3_set(&ret, data);
	return (ret);
}
