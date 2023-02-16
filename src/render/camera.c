#include "camera.h"
#include "render.h"
#include <math.h>
#include <libft.h>

t_camera camera_new(const t_vec3 *origin, double aspect_ratio, int hfov)
{
	const double viewport_width = 2.0 * tan(to_radians(hfov)/ 2);
	const double viewport_height = viewport_width / aspect_ratio;
	t_camera ret;

	ret.origin = *origin;
	ret.lower_left_corner = vec3_subtract_c(*origin, vec3_new((double []){viewport_width / 2, viewport_height / 2, 1}));
	ret.horizontal = vec3_new((VEC3_TYPE []){viewport_width, 0, 0});
	ret.vertical = vec3_new((VEC3_TYPE []){0, viewport_height, 0});
	return (ret);
}

t_ray camera_generate_ray(const t_camera *camera, double width_pct, double height_pct)
{
	t_vec3	direction;

	direction = camera->lower_left_corner;
	direction = vec3_add_c(direction, vec3_scalar(&camera->horizontal, width_pct));
	direction = vec3_add_c(direction, vec3_scalar(&camera->vertical, height_pct));

	direction = vec3_subtract(&direction, &camera->origin);

	return ((t_ray){.origin = camera->origin, .direction = direction});
}

