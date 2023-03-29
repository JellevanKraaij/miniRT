#include "render/hittables/cylinder.h"

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

t_hittable_data cylinder_new(const double radius, const double height)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return ((t_hittable_data){.data = NULL});
	cylinder->radius = radius;
	cylinder->topcenter.data[1] = height;
	return ((t_hittable_data){.data = cylinder, .type = CYLINDER});
}

void cylinder_destroy(void *data)
{
	free(data);
}

// double hit_cylinder(vec3 pixelVec, vec3 camera_origin, cylindrous cylin)
// {
// 	vec3 C = cylin.botcenter;
// 	vec3 H = cylin.topcenter;
// 	vec3 v = normalize_vec(vector_minus(pixelVec, camera_origin));
// 	vec3 w = vector_minus(pixelVec, C);
// 	vec3 h = normalize_vec(vector_minus(H, C));

// 	double a = (vector_product(v, v) - vector_product(v, h) * vector_product(v, h));
// 	double b = 2 * (vector_product(v, w) - (vector_product(v, h) * vector_product(w, h)));
// 	double c = vector_product(w, w) - pow(vector_product(w, h), 2) - (cylin.radius * cylin.radius);

// 	double discriminal = b * b - 4 * a * c;
// 	if (discriminal > 0)
// 		return ((-b - sqrt(discriminal)) / 2*a);
// 	return (0);
// }

bool cylinder_hit(const t_hittable *hittable, const t_ray *ray, t_hit_record *hit_record)
{
	double	a;
	double	c;
	double	half_b;
	double	discriminant;
	t_vec3	h; 
	t_vec3	w;

	w = vec3_subtract(&ray->origin, &hittable->center);
	h = vec3_normalize_c(vec3_subtract(&((t_cylinder *)hittable->data.data)->topcenter, &hittable->center));
	a = vec3_lenght_squared(&ray->direction) - vec3_dot(&ray->direction, &h) * vec3_dot(&ray->direction, &h);
	half_b = vec3_dot(&ray->direction, &w) - vec3_dot(&ray->direction, &h) * vec3_dot(&w, &h);
	c = vec3_lenght_squared(&w) - pow(vec3_dot(&w, &h), 2) - pow(((t_cylinder *)hittable->data.data)->radius, 2);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	double sqrtd = sqrt(discriminant);
	double root = (-half_b - sqrtd) / a;
	if (root < ray->min_distance || ray->max_distance < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < ray->min_distance || ray->max_distance < root)
			return (false);
	}
	if (hit_record == NULL)
		return (true);
	hit_record->distance = root;
	hit_record->point = ray_at(ray, root);
	hit_record->object = hittable;
	const t_vec3 normal = vec3_divide_c(vec3_subtract(&hit_record->point, &hittable->center), ((t_cylinder *)hittable->data.data)->radius);
	hit_record_set_normal(hit_record, ray, &normal);
	return (true);
}
