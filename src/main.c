#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <float.h>
#include <math.h>
#include "camera.h"
#include "ray.h"
#include "hittable/hittable.h"
#include "hittable/sphere.h"
#include "hittable/hittable_list.h"
#include "render.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

mlx_image_t	*g_img;

void	keyhook(mlx_key_data_t key, void *data)
{
	mlx_t	*mlx;

	mlx = data;
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
}

void	render(void);


int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	bzero(g_img->pixels, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_key_hook(mlx, keyhook, mlx);
	render();
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

bool hit_sphere(const t_vec3 *center, double radius, const t_ray *ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_subtract(&ray->origin, center);

	a = vec3_dot(&ray->direction, &ray->direction);
	b = 2.0 * vec3_dot(&oc, &ray->direction);
	c = vec3_dot(&oc, &oc) - (radius * radius);

	discriminant = (b * b) - (4 * a * c);
	return (discriminant > 0);
}

void	render(void)
{
	t_camera	camera;
	int	x;
	int	y;

	camera = camera_new(vec3_new(0, 0, 0), vec3_new(0, 0, -1), SCREEN_WIDTH / SCREEN_HEIGHT, 90);

	t_hittable_list *world = hittable_list_new(2);

	hittable_list_set(world, 0, hittable_new(vec3_new(1, 0, 5), (t_vec3){}, (uint8_t []){255, 0, 0}, sphere_new(0.5)));
	hittable_list_set(world, 1, hittable_new(vec3_new(-1, 0, 5), (t_vec3){}, (uint8_t []){0, 255, 0}, sphere_new(0.5)));
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			t_ray ray = camera_generate_ray(&camera, (double)x / (SCREEN_WIDTH - 1), (double)y / (SCREEN_HEIGHT - 1));
			t_hit_record hit_record = hittable_list_hit(world, &ray, 0, DBL_MAX);
			if (hit_record.hit)
				mlx_put_pixel(g_img, x, y, rgb_to_rgba(hit_record.object->color));
			else
				mlx_put_pixel(g_img, x, y, 0xFF000000);
			y++;
		}
		x++;
	}
}
