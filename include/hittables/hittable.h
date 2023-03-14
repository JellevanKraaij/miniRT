#ifndef HITTABLE_H
# define HITTABLE_H

#include <stdint.h>
#include <vec3.h>
#include "ray.h"
#include <stdbool.h>

typedef enum e_hittable_object_type
{
	ERROR = -1,
	SPHERE,
	PLANE
}	t_hittable_type;

typedef struct e_hittable_data
{
	void			*data;
	t_hittable_type	type;
}	t_hittable_data;

typedef struct s_hittable
{
	t_vec3	center;
	t_vec3	orientation;
	t_vec3	color;
	double  specular;

	t_hittable_data	data;
}	t_hittable;

typedef struct s_hit_record
{
	const t_hittable	*object;
	t_vec3	point;
	double	distance;
	t_vec3	normal;
}	t_hit_record;

t_hittable	*hittable_new(const t_vec3 center, const t_vec3 orientation, const t_vec3 color, double specular, t_hittable_data data);

bool hittable_hit(const t_hittable *hittable, const t_ray *ray, t_hit_record *hit_record);

void hittable_destroy(t_hittable *hittable);

#endif
