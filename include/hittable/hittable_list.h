#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <stddef.h>

typedef struct s_hittable_list
{
	t_hittable	**hittables;
	size_t		size;
}	t_hittable_list;

t_hittable_list *hittable_list_new(const size_t size);

void hittable_list_set(t_hittable_list *list, const size_t index, t_hittable *hittable);

void hittable_list_destroy(t_hittable_list *list);


t_hit_record hittable_list_hit(const t_hittable_list *list, const t_ray *ray, const double t_min, const double t_max);

#endif
