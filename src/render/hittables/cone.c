/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cone.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 16:17:25 by jvan-kra      #+#    #+#                 */
/*   Updated: 2023/06/05 16:17:25 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render/hittable.h"
#include <math.h>
#include <stddef.h>

t_cone	cone_new(const t_vec3 center, const t_vec3 orientation, \
	const double radius, const double height)
{
	t_cone	cone;

	cone.center = center;
	cone.orientation = vec3_normalize(&orientation);
	cone.radius = radius;
	cone.height = height;
	return (cone);
}

// void	initialize_cone_abc(const t_cone *cone, const t_ray *ray, \
// t_abc_vars *abc_vars)
// {
// 	abc_vars->relative_raypos = vec3_subtract(&ray->origin, &cone->center);
// 	abc_vars->a = vec3_dot(&ray->direction, &ray->direction) - \
// 	vec3_dot(&ray->direction, &cone->orientation) * \
// 	vec3_dot(&ray->direction, &cone->orientation);
// 	abc_vars->b = 2 * (vec3_dot(&ray->direction, &abc_vars->relative_raypos) - \
// 	(vec3_dot(&ray->direction, &cone->orientation) * \
// 	vec3_dot(&abc_vars->relative_raypos, &cone->orientation)));
// 	abc_vars->c = vec3_dot(&abc_vars->relative_raypos, \
// 	&abc_vars->relative_raypos) - (vec3_dot(&abc_vars->relative_raypos, \
// 	&cone->orientation) * vec3_dot(&abc_vars->relative_raypos, \
// 	&cone->orientation)) - \
// 	pow(cone->radius, 2);
// 	abc_vars->discriminant = pow(abc_vars->b, 2) - (4 * \
// 	abc_vars->a * abc_vars->c);
// }

void	initialize_cone_abc(const t_cone *cone, const t_ray *ray, \
t_abc_vars *abc_vars)
{
	// double point = vec3_add(&cone->center, vec3_multiply(&cone->height, &cone->orientation))
	double m = pow(cone->radius, 2) / pow(cone->height, 2);
	// double h = vec3_subtract(&cone->center, &point);
	// double w = vec3_subtract(&l, &h);
	// double v = ray->direction;

	// abc_vars->a = pow(v, 2) - m * pow(v*h, 2) - pow(v*h, 2);
	abc_vars->a = vec3_dot(&ray->direction, &ray->direction) - \
	vec3_dot(&ray->direction, &cone->orientation) * \
	vec3_dot(&ray->direction, &cone->orientation) * m - \
	vec3_dot(&ray->direction, &cone->orientation) * \
	vec3_dot(&ray->direction, &cone->orientation);

	// t_vec3 lel = vec3_dot(vec3_dot(&v, &h), vec3_dot(&w, &h));
	abc_vars->b = 2 * (vec3_dot(&ray->direction, &abc_vars->relative_raypos) - \
	m * (vec3_dot(&ray->direction, &cone->orientation) * \
	vec3_dot(&abc_vars->relative_raypos, &cone->orientation)) - \
	(vec3_dot(&ray->direction, &cone->orientation) * \
	vec3_dot(&abc_vars->relative_raypos, &cone->orientation)));

	// abc_vars->c = w*w - m * pow(w*h, 2) - pow(w*h, 2);
	abc_vars->c = vec3_dot(&abc_vars->relative_raypos, \
	&abc_vars->relative_raypos) - (m * ((vec3_dot(&abc_vars->relative_raypos, \
	&cone->orientation) * vec3_dot(&abc_vars->relative_raypos, \
	&cone->orientation)))) - (vec3_dot(&abc_vars->relative_raypos, \
	&cone->orientation) * vec3_dot(&abc_vars->relative_raypos, \
	&cone->orientation));

	abc_vars->discriminant = pow(abc_vars->b, 2) - (4 * \
	abc_vars->a * abc_vars->c);
}

t_vec3	cone_surface_normal(const t_cone *cone, const t_vec3 *point)
{
	const t_vec3	cp = vec3_subtract(point, &cone->center);
	const t_vec3	normal = vec3_subtract_c(cp, \
		vec3_scalar(&cone->orientation, vec3_dot(&cp, &cone->orientation)));

	return (vec3_divide(&normal, cone->radius));
}

bool	cone_width_hit(const t_cone *cone, const t_ray *ray, \
	double *distance)
{
	t_abc_vars	abc_vars;
	double		t[2];
	double		sqrtd;

	initialize_cone_abc(cone, ray, &abc_vars);
	if (abc_vars.discriminant < 0)
		return (false);
	sqrtd = sqrt(abc_vars.discriminant);
	t[0] = (-abc_vars.b - sqrtd) / (abc_vars.a * 2);
	t[1] = (-abc_vars.b + sqrtd) / (abc_vars.a * 2);
	if ((t[0] < ray->min_distance || t[0] > ray->max_distance) && \
		(t[1] < ray->min_distance || t[1] > ray->max_distance))
		return (false);
	if (fabs(t[0]) < fabs(t[1]))
	{
		distance[0] = t[0];
		distance[1] = t[1];
	}
	else
	{
		distance[0] = t[1];
		distance[1] = t[0];
	}
	return (true);
}

bool	cone_height_hit( const t_cone *cone, const t_ray *ray, \
	const double distance)
{
	t_vec3	point;
	double	cp_len;
	double	cq_len;

	if (distance < ray->min_distance || distance > ray->max_distance)
		return (false);
	point = ray_at(ray, distance);
	cp_len = vec3_length_c(vec3_subtract_c(point, cone->center));
	cq_len = sqrt((cp_len * cp_len) - (cone->radius * cone->radius));
	if (cq_len > (cone->height / 2))
		return (false);
	return (true);
}

// C = Point at the center of the base of the cone
// H = Point at the tip of the cone
// r = Cone base radius
// P = Point on the cone surface

// L0 = Point on the line
// v = Vector that defines the line direction

bool	cone_hit(const t_cone *cone, const t_ray *ray, \
	t_hit_record *hit_record)
{
	t_vec3		normal;
	double		t[2];
	double		distance;

	if (!cone_width_hit(cone, ray, t))
		return (false);
	distance = t[0];
	if (!cone_height_hit(cone, ray, t[0]))
	{
		if (!cone_height_hit(cone, ray, t[1]))
			return (false);
		distance = t[1];
	}
	if (hit_record == NULL)
		return (true);
	hit_record->distance = distance;
	hit_record->point = ray_at(ray, distance);
	normal = cone_surface_normal(cone, &hit_record->point);
	hit_record_set_normal(hit_record, ray, &normal);
	hit_record->ray_direction = ray->direction;
	hit_record->ray_origin = ray->origin;
	return (true);
}
