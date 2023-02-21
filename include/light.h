#ifndef LIGHT_H
# define LIGHT_H

# include <vec3.h>
# include "ray.h"

typedef struct s_light
{
	t_vec3  origin;
	t_vec3  color;
	double  brightness;
}   t_light;

t_light *light_new(const t_vec3 origin, const t_vec3 color, double brightness);
void    light_destroy(t_light *light);

t_ray light_generate_ray(const t_light *light, const t_vec3 *point);

#endif
