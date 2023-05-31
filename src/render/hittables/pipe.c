#include "render/hittable.h"
#include <stddef.h>
#include <math.h>


t_pipe	pipe_new(const t_vec3 center, const t_vec3 orientation, \
	const double radius, const double height)
{
	t_pipe	pipe;

	pipe.center = center;
	pipe.orientation = orientation;
	pipe.radius = radius;
	pipe.height = height;
	return (pipe);
}

void	initialize_pipe_abc(const t_pipe *pipe, const t_ray *ray, \
t_abc_vars *abc_vars)
{
	abc_vars->relative_raypos = vec3_subtract(&ray->origin, &pipe->center);
	abc_vars->a = vec3_dot(&ray->direction, &ray->direction) - \
	vec3_dot(&ray->direction, &pipe->orientation) * \
	vec3_dot(&ray->direction, &pipe->orientation);
	abc_vars->b = 2 * (vec3_dot(&ray->direction, &abc_vars->relative_raypos) - \
	(vec3_dot(&ray->direction, &pipe->orientation) * \
	vec3_dot(&abc_vars->relative_raypos, &pipe->orientation)));
	abc_vars->c = vec3_dot(&abc_vars->relative_raypos, \
	&abc_vars->relative_raypos) - (vec3_dot(&abc_vars->relative_raypos, \
	&pipe->orientation) * vec3_dot(&abc_vars->relative_raypos, \
	&pipe->orientation)) - \
	pow(pipe->radius, 2);
	abc_vars->discriminant = pow(abc_vars->b, 2) - (4 * \
	abc_vars->a * abc_vars->c);
}

bool	pipe_with_hit(const t_pipe *pipe, const t_ray *ray)
{
	t_abc_vars	abc_vars;

	initialize_cylinder_abc(pipe, ray, &abc_vars);
	abc_vars.discriminant = pow(abc_vars.b, 2) - (4 * \
	abc_vars.a * abc_vars.c);
	if (abc_vars.discriminant < 0)
		return (false);
	cylinder_vars->sqrtd = sqrt(abc_vars.discriminant);
	cylinder_vars->root = (-abc_vars.b - cylinder_vars->sqrtd) / \
	(abc_vars.a * 2);
	if (cylinder_vars->root < ray->min_distance || ray->max_distance < \
	cylinder_vars->root)
	{
		cylinder_vars->root = (-abc_vars.b + cylinder_vars->sqrtd) / \
		(abc_vars.a * 2);
		if (cylinder_vars->root < ray->min_distance || ray->max_distance < \
		cylinder_vars->root)
			return (false);
	}
	return (true);
}

bool	pipe_hit(const t_pipe *pipe, const t_ray *ray, \
	t_hit_record *hit_record)
{
	const double	t = vec3_dot_c(vec3_subtract(&pipe->center, \
		&ray->origin), pipe->orientation) / \
		vec3_dot(&ray->direction, &pipe->orientation);
	t_vec3			point;

	if (t < ray->min_distance || t > ray->max_distance)
		return (false);
	point = ray_at(ray, t);
	if (vec3_lenght_c(vec3_subtract(&pipe->center, &point)) > \
		pipe->radius)
		return (false);
	if (hit_record == NULL)
		return (true);
	hit_record->distance = t;
	hit_record->point = point;
	hit_record_set_normal(hit_record, ray, &pipe->orientation);
	hit_record->ray_direction = ray->direction;
	hit_record->ray_origin = ray->origin;
	return (true);
}
