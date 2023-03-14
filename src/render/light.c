#include "light.h"
#include "render.h"

#include <stdlib.h>

t_light *light_new(const t_vec3 origin, const t_vec3 color, double brightness)
{
	t_light *new;

	new = malloc(sizeof(t_light));
	if (new == NULL)
		return (NULL);
	new->origin = origin;
	new->color = vec3_scalar(&color, brightness);
	return (new);
}

void light_destroy(t_light *light)
{
	free(light);
}

t_ray light_generate_ray(const t_light *light, const t_vec3 *point)
{
	const t_vec3 direction = vec3_subtract(&light->origin, point);\

	return (ray_new(point, &direction, RENDER_SHADOW_BIAS, vec3_lenght(&direction)));
}
