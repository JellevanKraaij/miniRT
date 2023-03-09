#ifndef RENDER_H
# define RENDER_H

#include "hittables/hittable.h"
#include "hittables/array.h"
#include "camera.h"
#include "light.h"

#include <stdint.h>

#define RENDER_SHADOW_BIAS 0.0001

typedef int (*t_putpixel_f)(uint32_t x, uint32_t y, uint32_t color, void *data);

typedef struct s_render_params
{
	uint32_t	width;
	uint32_t	height;
	t_putpixel_f	putpixel_f;
	void			*putpixel_data;

	t_hittable_array *hittables;
	t_light 		*light;
	t_camera		*camera;

}	t_render_params;

t_render_params *render_params_new(void);
void render_params_destroy(t_render_params *render_params);

int	render(t_render_params *render_params);

double to_degrees(double radians);
double to_radians(double degrees);
uint32_t	convert_color(const t_vec3 *color);

#endif
