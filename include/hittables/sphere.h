#ifndef SPHERE_H
#define SPHERE_H

#include "hittables/hittable.h"
#include "ray.h"

typedef struct s_sphere
{
	double	radius;
}	t_sphere;

t_hittable_data	sphere_new(const double radius);
bool 			sphere_hit(const t_hittable *hittable, const t_ray *ray, t_hit_record *hit_record);
void			sphere_destroy(void *data);

#endif
