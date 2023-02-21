#include "render.h"
#include "hittables/hittable.h"
#include "hittables/array.h"
#include  <float.h>
#include <stdio.h>

double screenx_to_modelx(uint32_t x, uint32_t width)
{
	return ((double)x / (width - 1));
}

double screeny_to_modely(uint32_t y, uint32_t height)
{
	return (1.0 - ((double)y / (height - 1)));
}

int	render(t_render_params *render_params)
{
	const t_vec3	background_color = vec3_new(0, 0, 0);
	const t_vec3	ambient_color = vec3_new(50, 50, 50);
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < render_params->width)
	{
		y = 0;
		while (y < render_params->height)
		{
			t_ray ray = camera_generate_ray(render_params->camera, screenx_to_modelx(x, render_params->width), screeny_to_modely(y, render_params->height));
			t_hit_record hit_record = hittable_array_hit(render_params->hittables, &ray, 0, DBL_MAX);
			if (hittable_is_hit(&hit_record))
			{
				t_ray light_ray = light_generate_ray(render_params->light, &hit_record.point);
				t_hit_record light_hit_record = hittable_array_hit(render_params->hittables, &light_ray, 0.01, DBL_MAX);
				if (!hittable_is_hit(&light_hit_record))
					render_params->putpixel_f(x, y, convert_color(&hit_record.object->color), render_params->putpixel_data);
				else
					render_params->putpixel_f(x, y, convert_color(&ambient_color), render_params->putpixel_data);
			}
			else
				render_params->putpixel_f(x, y, convert_color(&background_color), render_params->putpixel_data);
			y++;
		}
		x++;
	}
	return (0);
}
