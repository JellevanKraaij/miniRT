#include "camera.h"
#include "render.h"
#include <math.h>
#include <libft.h>

static t_vec3	*camera_calculate_corner(const t_vec3 *origin, double viewport_width, double viewport_height, double focal_length)
{
	t_vec3 *ret;
	t_vec3 *tmp;

	tmp = mat_vec3_new();
	if (tmp == NULL)
		return(NULL);
	mat_vec3_set(tmp, (double []){viewport_width / 2, viewport_height / 2, focal_length});
	ret = mat_subtract(origin, tmp);
	mat_free(tmp);
	return (ret);
}

t_camera *camera_new(const t_vec3 *origin, double aspect_ratio, int hfov)
{
	const double viewport_width = 2.0 * tan(to_radians(hfov)/ 2);
	const double viewport_height = viewport_width / aspect_ratio;
	t_camera *ret;

	ret = ft_calloc(1, sizeof(t_camera));
	if (ret == NULL)
		return (NULL);
	ret->origin = mat_dup(origin);
	ret->horizontal = mat_vec3_new();
	ret->vertical = mat_vec3_new();
	ret->lower_left_corner = camera_calculate_corner(origin, viewport_width, viewport_height, 1);
	if (ret->origin == NULL || ret->horizontal == NULL || ret->vertical == NULL || ret->lower_left_corner == NULL)
		return (camera_destroy(ret), NULL);
	mat_vec3_set(ret->horizontal, (MAT_TYPE []){viewport_width, 0, 0});
	mat_vec3_set(ret->vertical, (MAT_TYPE []){0, viewport_height, 0});
	return (ret);
}

t_ray *camera_generate_ray(const t_camera *camera, double width_pct, double height_pct)
{
	t_ray	*ret;
	t_vec3	*direction;
	t_vec3	*horizontal_movement;
	t_vec3	*vertical_movement;


	direction = mat_dup(camera->lower_left_corner);
	horizontal_movement = mat_multiply_scalar(camera->horizontal, width_pct);
	vertical_movement = mat_multiply_scalar(camera->vertical, height_pct);
	
	if (direction == NULL || horizontal_movement == NULL || vertical_movement == NULL)
		return (mat_free(direction), mat_free(horizontal_movement), mat_free(vertical_movement), NULL);
	mat_add_assign(direction, horizontal_movement);
	mat_free(horizontal_movement);
	mat_add_assign(direction, vertical_movement);
	mat_free(vertical_movement);
	mat_subtract_assign(direction, camera->origin);
	ret = ray_new(camera->origin, direction);
	mat_free(direction);
	return (ret);
}

void camera_destroy(t_camera *camera)
{
	if (camera == NULL)
		return ;
	mat_free(camera->origin);
	mat_free(camera->horizontal);
	mat_free(camera->vertical);
	mat_free(camera->lower_left_corner);
	free(camera);
}

