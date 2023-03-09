#ifndef PLANE_H
#define PLANE_H

#include "hittables/hittable.h"
#include "ray.h"

t_hittable_data	plane_new(void);
bool 			plane_hit(const t_hittable *hittable, const t_ray *ray, t_hit_record *hit_record);
void			plane_destroy(void *data);

#endif