#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

void draw_camera_and_circle(int x, int y, int x_mid, int y_mid, int size, \
	mlx_image_t *g_img)
{
	float FOV = 0.75;

	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if ((y - HEIGHT/2) > -FOV*x && (y - HEIGHT/2) < FOV*x)
				mlx_put_pixel(g_img, x, y, 0xFEDD00FF);
			if (((x - x_mid) * (x - x_mid) + (y - y_mid) * (y - y_mid)) <= size)
				mlx_put_pixel(g_img, x, y, 0x74D1EAFF);
			x++;
		}
		x = 0;
		y++;
	}
}

void shadows(int x, int y, int x_mid, int y_mid, \
	int size, mlx_image_t *g_img)
{
	float ray_x = 0;
	float ray_y;

	ray_y = (float)(y - y_mid) / (float)x;
	while ((ray_x < WIDTH) && (((ray_x - x) * ray_y + y) > 0) && \
	(((ray_x - x)* ray_y + y) < HEIGHT))
	{
		if ((ray_x - x > 0) && (((ray_x - x_mid) * \
		(ray_x - x_mid) + ((ray_x - x) * ray_y + y - y_mid) * \
		((ray_x - x) * ray_y + y - y_mid)) > size))
			mlx_put_pixel(g_img, ray_x, (ray_x - x) * ray_y + y, 0x440099FF);
		ray_x++;
	}
}

void intersect_objects(int x, int y, int x_mid, int y_mid, int size, \
	mlx_image_t *g_img)
{
	float FOV = 0.75;

	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (((y > (-FOV*x + y_mid)) && (y < (FOV*x + y_mid))) && \
			(((x - x_mid) * (x - x_mid) + (y - y_mid) * \
				(y - y_mid)) <= size))
			{
				mlx_put_pixel(g_img, x, y, 0xe40909FF);
				shadows(x, y, x_mid, y_mid, size, g_img);
				break ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void lazor(int x_mid, int y_mid, int size, mlx_image_t *g_img)
{
	float FOV = 0.75;
	float x = 0;
	float angle = .2;
	float hitpoint;
	while (x < WIDTH)
	{
		if ((angle * x + y_mid > 0) && (angle * x + y_mid < HEIGHT))
			mlx_put_pixel(g_img, x, angle * x + y_mid, 0xe40909FF);
		if (((angle * x + y_mid > (-FOV*x + y_mid)) && (angle * x + y_mid < \
			(FOV*x + y_mid))) && (((x - x_mid) * (x - x_mid) + (angle * x) * \
				(angle * x)) <= size))
			break ;
		x++;
	}
	hitpoint = angle * x + y_mid;
	float saved_x = x;
	float diff_y = y_mid - hitpoint;
	float diff_x = x_mid - x;
	float new_angle = diff_y / diff_x;
	float whatevs = (new_angle * x_mid - y_mid) * -1;
	x = 0;
	while (x < WIDTH / 2)
	{
		if ((new_angle * x + whatevs > 0) && (new_angle * x + whatevs < HEIGHT))
		mlx_put_pixel(g_img, x, new_angle * x + whatevs, 0xe40909FF);
		x++;
	}
	float diff_c = diff_x * diff_x + diff_y * diff_y;
	diff_x = diff_x / sqrt(diff_c);
	diff_y = diff_y / sqrt(diff_c);
	float new_vecca_x;
	float new_vecca_y;
	// (1, angle) -2 * (diff_x, diff_y) * (diff_x * 1, diff_y * angle)
	new_vecca_x = 1 -2 * diff_x * (diff_x + diff_y * angle);
	new_vecca_y = angle -2 * diff_y * (diff_y * angle + diff_x);
	float new_vec_vec = new_vecca_y / new_vecca_x;
	float another = (saved_x * new_vec_vec -hitpoint) * -1;
	x = 0;
	while (x < WIDTH)
	{
		if (new_vecca_y > 0)
		{
			if (((x * new_vec_vec) + another > hitpoint) && \
				((x * new_vec_vec) + another < HEIGHT))
			mlx_put_pixel(g_img, x, (x * new_vec_vec) + another, 0xe40909FF);
		}
		if (new_vecca_y < 0)
		{
			if (((x * new_vec_vec) + another > 0) && \
				((x * new_vec_vec) + another < hitpoint))
			mlx_put_pixel(g_img, x, (x * new_vec_vec) + another, 0xe40909FF);
		}
		x++;
	}
}

int32_t	main(void)
{
	int y_mid = HEIGHT/2;
	int x_mid = WIDTH/2;
	int size = 2500;
	float FOV = 0.75;
	int x = 0;
	int y = 0;
	mlx_t	*mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	mlx_image_t	*g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	draw_camera_and_circle(x, y, x_mid, y_mid, size, g_img);
	intersect_objects(x, y, x_mid, y_mid, size, g_img);
	lazor(x_mid, y_mid, size, g_img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
