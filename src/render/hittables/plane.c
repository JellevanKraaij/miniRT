#include "hittables/plane.h"

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

t_hittable_data plane_new(void)
{
	return ((t_hittable_data){.data = NULL, .type = PLANE});
}

void plane_destroy(void *data)
{
	(void)data;
}

t_hit_record plane_hit(const t_hittable *hittable, const t_ray *ray, const double t_min, const double t_max)
{
	double		denominator;

	denominator = vec3_dot(&ray->direction, &hittable->orientation);
	if (fabs(denominator) < 0.00001)
		return ((t_hit_record){.hit = false});
	double		t = vec3_dot(&hittable->center, &hittable->orientation) / denominator;
	if (t < t_min || t > t_max)
		return ((t_hit_record){.hit = false});
	return ((t_hit_record){.hit = true, .distance = t, .point = ray_at(ray, t), .object = hittable});
}
