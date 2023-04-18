#include "render/hittables/sphere.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

t_hittable_data	sphere_new(const double radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return ((t_hittable_data){.data = NULL, .type = ERROR});
	sphere->radius = radius;
	return ((t_hittable_data){.data = sphere, .type = SPHERE});
}

void	sphere_destroy(void *data)
{
	free(data);
}

void	initialize_sphere_abc(const t_hittable *hittable, const t_ray *ray, \
t_hit_vars *hit_vars)
{
	hit_vars->ray_pos = vec3_subtract(&ray->origin, &hittable->center);
	hit_vars->a = vec3_lenght_squared(&ray->direction);
	hit_vars->b = vec3_dot(&hit_vars->ray_pos, &ray->direction);
	hit_vars->c = vec3_lenght_squared(&hit_vars->ray_pos) - \
	pow((((t_sphere *)hittable->data.data)->radius, 2));
	hit_vars->discriminant = pow(hit_vars->b, 2) - hit_vars->a * hit_vars->c;
}

void	hit_record_assignment(const t_hittable *hittable, const t_ray *ray, \
t_hit_record *hit_record, double root)
{
	t_vec3	normal;

	hit_record->distance = root;
	hit_record->point = ray_at(ray, root);
	hit_record->object = hittable;
	normal = vec3_divide_c(vec3_subtract(&hit_record->point, \
	&hittable->center), ((t_sphere *)hittable->data.data)->radius);
	hit_record_set_normal(hit_record, ray, &normal);
	hit_record->ray_direction = ray->direction;
	hit_record->ray_origin = ray->origin;
}

bool	sphere_hit(const t_hittable *hittable, const t_ray *ray, \
	t_hit_record *hit_record)
{
	t_hit_vars	hit_vars;
	double		root;

	initialize_sphere_abc(hittable, ray, &hit_vars);
	if (hit_vars.discriminant < 0)
		return (false);
	root = (-hit_vars.b - sqrt(hit_vars.discriminant)) / hit_vars.a;
	if (root < ray->min_distance || ray->max_distance < root)
	{
		root = (-hit_vars.b + sqrt(hit_vars.discriminant)) / hit_vars.a;
		if (root < ray->min_distance || ray->max_distance < root)
			return (false);
	}
	if (hit_record == NULL)
		return (true);
	hit_record_assignment(hittable, ray, hit_record, root);
	return (true);
}
