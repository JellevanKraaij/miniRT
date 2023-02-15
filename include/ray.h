#ifndef RAY_H
#define RAY_H

#include <matrix3d.h>

typedef struct s_ray
{
	t_vec3	*origin;
	t_vec3	*direction;
} t_ray;

t_ray *ray_new(const t_vec3 *origin, const t_vec3 *direction);
void ray_destroy(t_ray *ray);

t_vec3 *ray_at(const t_ray *ray, double distance);

#endif
