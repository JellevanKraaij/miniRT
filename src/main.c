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

int32_t	main(void)
{
	printf("hello\n");
	int x = 0;
	int y = 0;
	int z = 0;
	mlx_t	*mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	mlx_image_t	*g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);

	// draw camera or lightsource, with adjustable FOV
	float FOV = 0.75;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			printf("%d\n", y);
			if ((y > (-FOV*x + HEIGHT/2)) && (y < (FOV*x + HEIGHT/2)))
				mlx_put_pixel(g_img, x, y, 0xFEDD00FF);
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;

	// draw circle
	int circle_size = 2500;
	int circle_x_mid = WIDTH/2;
	int circle_y_mid = HEIGHT/2;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			printf("%d\n", y);
			if (((x - WIDTH/2) * (x - WIDTH/2) + (y - HEIGHT/2) * \
				(y - HEIGHT/2)) <= circle_size)
				mlx_put_pixel(g_img, x, y, 0x74D1EAFF);
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;

	float hit_x;
	float hit_y;
	float ray_x = 0;
	float ray_y = 0;

	// show intersections (hitpoints)
	int hit_point_object[100][2];
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (((y > (-FOV*x + HEIGHT/2)) && (y < (FOV*x + HEIGHT/2))) && \
			(((x - WIDTH/2) * (x - WIDTH/2) + (y - HEIGHT/2) * (y - HEIGHT/2)) \
				<= circle_size))
			{
				hit_point_object[z][0] = x;
				hit_point_object[z][1] = y;
				mlx_put_pixel(g_img, x, y, 0xe40909FF);
				hit_x = hit_point_object[z][0];// - origin_camera[0];
				hit_y = hit_point_object[z][1] - HEIGHT/2;
				z++;
				ray_y = hit_y / hit_x;
				printf("%f\n", hit_y / hit_x);
				while ((ray_x < WIDTH) && (((ray_x - x) * ray_y + y) > 0) && (((ray_x - x)* ray_y + y) < HEIGHT))
				{
					if ((ray_x - x > 0) && \
					(((ray_x - WIDTH/2) * (ray_x - WIDTH/2) + \
					((ray_x - x) * ray_y + y - HEIGHT/2) * ((ray_x - x) * ray_y + y - HEIGHT/2)) > circle_size))
						mlx_put_pixel(g_img, ray_x, (ray_x - x) * ray_y + y, 0x440099FF);
					ray_x++;
				}
				if (y < HEIGHT / 2)
				{
					float diff_x = circle_x_mid - x;
					float diff_y = circle_y_mid - y;
					float exponent = diff_y / diff_x;
					float super_c = ((exponent * x) - y) * -1;
					
					x = 0;
					while (x < WIDTH / 2)
					{
						if ((((x * exponent)) + super_c < HEIGHT / 2) && \
						((x * exponent) + super_c > 0))
							mlx_put_pixel(g_img, x, (x * exponent) \
							+ super_c,  0xe40909FF);
						x++;
					}
				}
				break ;
			}
			x++;
		}
		ray_x = 0;
		x = 0;
		y++;
	}
	z--;

	// calculate and print degrees
	
	int origin_camera[2];
	origin_camera[0] = 0;
	origin_camera[1] = HEIGHT/2;

	// printf("%d\n", z);
	// while (z > -1)
	// {
	// 	hit_x = hit_point_object[z][0] - origin_camera[0];
	// 	hit_y = hit_point_object[z][1] - origin_camera[1];
	// 	printf("%f\n", hit_y / hit_x);
	// 	z--;
	// }

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


// startpunt = max -c
// daarna naa hetzelfde punt toe