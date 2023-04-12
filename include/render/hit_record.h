#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <vec3.h>

typedef struct s_hit_record t_hit_record;

#include "hittables/hittable.h"

struct s_hit_record
{
	const t_hittable	*object;
	t_vec3	point;
	double	distance;
	t_vec3	normal;
	t_vec3  outward_normal;

	t_vec3	ray_direction;
	t_vec3  ray_origin;
};

void hit_record_set_normal(t_hit_record *record, const t_ray *ray, const t_vec3 *outward_normal);

#endif
