#include <hittables/hittable.h>
#include "hittables/sphere.h"
#include "hittables/plane.h"
#include "ray.h"

#include <libft.h>
#include <float.h>
#include <stdbool.h>

typedef void (*t_hittable_destroy_f)(void *);
typedef t_hit_record (*t_hittable_hit_f)(const t_hittable *, const t_ray *, double, double);

static const t_hittable_destroy_f	g_hittable_destroy_f[] = {
	[SPHERE] = sphere_destroy,
	[PLANE] = plane_destroy
};

static const t_hittable_hit_f	g_hittable_hit_f[] = {
	[SPHERE] = sphere_hit,
	[PLANE] = plane_hit
};

t_hittable	*hittable_new(const t_vec3 center, const t_vec3 orientation, const t_vec3 color, t_hittable_data data)
{
	t_hittable	*new;

	if (data.type == ERROR)
		return (NULL);
	new = malloc(sizeof(t_hittable));
	if (new == NULL)
		return (NULL);
	new->center = center;
	new->orientation = orientation;
	new->color = color;
	new->data = data;
	return (new);
}

void hittable_destroy(t_hittable *hittable)
{
	if (hittable == NULL)
		return ;
	g_hittable_destroy_f[hittable->data.type](hittable->data.data);
	free(hittable);
}

t_hit_record hittable_hit(const t_hittable *hittable, const t_ray *ray, const double t_min, const double t_max)
{
	return (g_hittable_hit_f[hittable->data.type](hittable, ray, t_min, t_max));
}

bool hittable_is_hit(const t_hit_record *record)
{
	return (record->hit);
}
