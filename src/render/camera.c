#include "camera.h"
#include "render.h"
#include <math.h>
#include <libft.h>
#include <float.h>
 
# include <stdio.h>

t_camera *camera_new(const t_vec3 position, const t_vec3 direction, double aspect_ratio, double hfov)
{
	t_camera *ret = malloc(sizeof(t_camera));
	if (ret == NULL)
		return (NULL);

	camera_update(ret, position, direction, aspect_ratio, hfov);
	return (ret);
}

void camera_update(t_camera *camera, const t_vec3 position, const t_vec3 direction, double aspect_ratio, double hfov)
{
	camera->position = position;
	camera->direction = direction;
	camera->aspect_ratio = aspect_ratio;
	camera->hfov = hfov;
}

void camera_prepare(t_camera *camera)
{
	const t_vec3	camera_up = vec3_new(0, 1, 0);
	const double viewport_width = 2.0 * tan(to_radians(camera->hfov) / 2);
	const double viewport_height = viewport_width / camera->aspect_ratio;
	

	t_vec3	w = vec3_normalize_c(vec3_reverse(&camera->direction));
	t_vec3	u = vec3_normalize_c(vec3_cross(&w, &camera_up));
	t_vec3	v = vec3_cross(&u, &w);
	
	camera->horizontal = vec3_scalar(&u, viewport_width);
	camera->vertical = vec3_scalar(&v, viewport_height);

	t_vec3 half_horizontal = vec3_divide(&camera->horizontal, 2);
	t_vec3 half_vertical = vec3_divide(&camera->vertical, 2);

	camera->lower_left_corner = vec3_subtract_c(vec3_subtract_c(vec3_subtract_c(camera->position, half_horizontal), half_vertical), w);
}

t_ray camera_generate_ray(const t_camera *camera, double width_pct, double height_pct)
{
	t_vec3	direction;

	direction = camera->lower_left_corner;
	direction = vec3_add_c(direction, vec3_scalar(&camera->horizontal, width_pct));
	direction = vec3_add_c(direction, vec3_scalar(&camera->vertical, height_pct));

	direction = vec3_subtract(&direction, &camera->position);

	return (ray_new(&camera->position, &direction, 0, DBL_MAX));
}

void camera_destroy(t_camera *camera)
{
	free(camera);
}
