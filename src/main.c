#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <float.h>
#include <math.h>
#include "camera.h"
#include "ray.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#include "config.h"

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
	// printf("ray origin: "); mat_print(ray->origin);
	// printf("ray direction: "); mat_print(ray->direction);

	a = vec3_dot(&ray->direction, &ray->direction);
	b = 2.0 * vec3_dot(&oc, &ray->direction);
	c = vec3_dot(&oc, &oc) - (radius * radius);

	// printf("a: %f b: %f c: %f\n", a, b, c);

	discriminant = (b * b) - (4 * a * c);
	// printf("discriminant %f\n", discriminant);
	return (discriminant > 0);
}

void	render(void)
{
	t_camera	camera;
	int	x;
	int	y;
	t_vec3	origin;

	origin = vec3_new((double []){0, 0, 0});
	camera = camera_new(&origin, SCREEN_WIDTH / SCREEN_HEIGHT, 90);
	x = 0;

	// printf("camera horizontal: "); mat_print(camera->horizontal);
	// printf("camera vertical: "); mat_print(camera->vertical);
	// printf("camera corner: "); mat_print(camera->lower_left_corner);

	// t_ray *test = camera_generate_ray(camera, 0.5, 0.5);

	// printf("ray origin: "); mat_print(test->origin);
	// printf("ray direction: "); mat_print(test->direction);

	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			t_ray ray = camera_generate_ray(&camera, (double)x / (SCREEN_WIDTH - 1), (double)y / (SCREEN_HEIGHT - 1));
			
			t_vec3 sphere_origin = vec3_new((double []){0, 0, -1});
			if (hit_sphere(&sphere_origin, 0.5, &ray))
				mlx_put_pixel(g_img, x, y, 0xFF0000FF);
			else
				mlx_put_pixel(g_img, x, y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}
