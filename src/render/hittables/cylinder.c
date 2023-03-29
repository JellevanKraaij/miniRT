#include "render/hittables/cylinder.h"

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include <stdio.h>

t_hittable_data cylinder_new(const double radius, const double height)
{
	t_cylinder	*cylinder;
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return ((t_hittable_data){.data = NULL, .type = ERROR});
	cylinder->radius = radius;
	cylinder->height = height;
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
	t_vec3	oc = vec3_subtract(&ray->origin, &hittable->center);
	double a = vec3_dot(&ray->direction, &ray->direction) - vec3_dot(&ray->direction, &hittable->orientation) * vec3_dot(&ray->direction, &hittable->orientation);
	double b = 2 * (vec3_dot(&ray->direction, &oc) - (vec3_dot(&ray->direction, &hittable->orientation) * vec3_dot(&oc, &hittable->orientation)));
	double c = vec3_dot(&oc, &oc) - (vec3_dot(&oc, &hittable->orientation) * vec3_dot(&oc, &hittable->orientation)) - (((t_cylinder *)hittable->data.data)->radius * ((t_cylinder *)hittable->data.data)->radius);
	
	double discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (false);
	
	double sqrtd = sqrt(discriminant);
	double root = (-b - sqrtd) / (a * 2);
	if (root < ray->min_distance || ray->max_distance < root)
	{
		root = (-b + sqrtd) / (a * 2);
		if (root < ray->min_distance || ray->max_distance < root)
			return (false);
	}

	t_vec3 point = ray_at(ray, root);

	t_vec3 CP = vec3_subtract(&point, &hittable->center);
	double CP_len = vec3_lenght(&CP);

	double CQ_len = sqrt((CP_len * CP_len) - (((t_cylinder *)hittable->data.data)->radius * ((t_cylinder *)hittable->data.data)->radius));

	if (CQ_len > ((t_cylinder *)hittable->data.data)->height / 2)
		return (false);

	if (hit_record == NULL)
		return (true);

	hit_record->distance = root;
	hit_record->point = point;
	hit_record->object = hittable;
	


	// printf ("CP_len: %f CQ_len: %f radius: %f\n", CP_len, CQ_len, ((t_cylinder *)hittable->data.data)->radius);

	t_vec3 CQ = vec3_scalar(&hittable->orientation, CQ_len);

	t_vec3 Q = vec3_add(&hittable->center, &CQ);

	t_vec3 normal = vec3_subtract(&hit_record->point, &Q);

	normal = vec3_normalize(&normal);

	hit_record_set_normal(hit_record, ray, &normal);
	return (true);
}
