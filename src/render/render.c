#include "render.h"
#include "hittables/hittable.h"
#include "hittables/array.h"
#include  <float.h>
#include <stdio.h>
#include <math.h>

double screenx_to_modelx(uint32_t x, uint32_t width)
{
	return ((double)x / (width - 1));
}

double screeny_to_modely(uint32_t y, uint32_t height)
{
	return (1.0 - ((double)y / (height - 1)));
}

t_vec3 vec3_reflect(const t_vec3 *v, const t_vec3 *n)
{
	t_vec3 reflected = vec3_subtract_c(*v, vec3_scalar_c(*n, 2 * vec3_dot(v, n)));
	return (reflected);
}

t_vec3 calculate_specular_light(const t_light *light, const t_ray *light_ray, const t_ray *camera_ray, const t_hit_record *hit_record)
{
	t_vec3 specular_light = light->color;

	t_vec3 reflected = vec3_reflect(&light_ray->direction, &hit_record->normal);
	double specular_factor = vec3_dot(&reflected, &camera_ray->direction);

	if (specular_factor > 0)
		color_scale(&specular_light, pow(specular_factor, hit_record->object->specular));
	else
		color_scale(&specular_light, 0);
	return (specular_light);

}

t_vec3 calculate_light_factor(const t_light *light, const t_ray *light_ray, const t_hit_record *hit_record)
{
	t_vec3 light_factor = light->color;
	double light_dot_normal = vec3_dot(&hit_record->normal, &light_ray->direction);
	if (light_dot_normal < 0)
		light_dot_normal =  vec3_dot_c(hit_record->normal, vec3_subtract_c(vec3_new(0,0,0), light_ray->direction));
	color_scale(&light_factor, light_dot_normal);
	return (light_factor);
}

int	render(t_render_params *render_params)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < render_params->width)
	{
		y = 0;
		while (y < render_params->height)
		{
			t_ray ray = camera_generate_ray(render_params->camera, screenx_to_modelx(x, render_params->width), screeny_to_modely(y, render_params->height));
			t_hit_record hit_record;
			if (hittable_array_hit(render_params->hittables, &ray, &hit_record))
			{
				t_vec3 light = vec3_new(0,0,0);
				const t_vec3 *obj_color = &hit_record.object->color;
	
				t_ray light_ray = light_generate_ray(render_params->light, &hit_record.point);
				if (!hittable_array_hit(render_params->hittables, &light_ray, NULL))
				{
					t_vec3 point_light = calculate_light_factor(render_params->light, &light_ray, &hit_record);
					color_add(&light, obj_color, &point_light);

					t_vec3 specular_light = calculate_specular_light(render_params->light, &light_ray, &ray, &hit_record);
					t_vec3 white = vec3_new(1,1,1);
					color_add(&light, &white, &specular_light);
				}
				color_add(&light, obj_color, &render_params->ambient_light);
				render_params->putpixel_f(x, y, color_to_uint32(&light), render_params->putpixel_data);
			}
			else
				render_params->putpixel_f(x, y, 0xFF, render_params->putpixel_data);
			y++;
		}
		x++;
	}
	return (0);
}
