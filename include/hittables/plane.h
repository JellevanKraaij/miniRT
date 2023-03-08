#ifndef PLANE_H
#define PLANE_H

#include "hittables/hittable.h"
#include "ray.h"

t_hittable_data	plane_new(void);
t_hit_record	plane_hit(const t_hittable *hittable, const t_ray *ray, const double t_min, const double t_max);
void			plane_destroy(void *data);

#endif
