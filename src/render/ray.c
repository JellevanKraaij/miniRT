#include "ray.h"
#include <libft.h>

t_ray *ray_new(const t_vec3 *origin, const t_vec3 *direction)
{
	t_ray *ret;

	ret = ft_calloc(1, sizeof(t_ray));
	if (ret == NULL)
		return (NULL);
	ret->origin = mat_dup(origin);
	ret->direction = mat_dup(direction);
	if (ret->origin == NULL || ret->direction == NULL)
		return (ray_destroy(ret), NULL);
	return (ret);
}

void ray_destroy(t_ray *ray)
{
	if (ray == NULL)
		return ;
	mat_free(ray->origin);
	mat_free(ray->direction);
	free(ray);
}

t_vec3	*ray_at(const t_ray *ray, double distance)
{
	t_vec3	*ret;

	ret = mat_multiply_scalar(ray->direction, distance);
	if (ret == NULL)
		return (NULL);
	mat_add_assign(ret, ray->origin);
	return (ret);
}
