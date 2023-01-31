#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <float.h>
#include <math.h>

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

#define VIEWPORT_WIDTH 10
#define VIEWPORT_HEIGHT 10

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

double *CanvasToViewport(int x, int y, double depth)
{
	double *ret = malloc(sizeof(double) * 3);

	ret[X] = (double)x * ((double)VIEWPORT_WIDTH / (double)SCREEN_WIDTH);
	ret[Y] = (double)y * ((double)VIEWPORT_HEIGHT / (double)SCREEN_HEIGHT);
	ret[Z] = depth;
	return (ret);
}

double dot_product(double *v, double *u, int n)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
        result += v[i] * u[i];
    return result;
}

typedef struct sphere_s {
	double radius;
	double position[3];
	uint32_t color;
} sphere_t;

double *IntersectRaySphere(double *origin, double *destination, sphere_t *sphere)
{
	double a = dot_product(destination, destination, 3);
	double b = 2 * dot_product(sphere->position, destination, 3);
	double c = dot_product(sphere->position, sphere->position, 3) - (sphere->radius * sphere->radius);

	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (NULL);
	double *ret = malloc(sizeof(double) * 2);

	ret[0] = (-b + sqrt(discriminant)) / (2*a);
    ret[1] = (-b - sqrt(discriminant)) / (2*a);
	return ret;
}

const uint32_t sphere_cnt = 3;
sphere_t spheres[sphere_cnt] = {
{.radius = 5, .position = {5, 0, 60}, .color = 0xFFFF00FF},
{.radius = 5, .position = {0, 0, 66}, .color = 0x00FF00FF},
{.radius = 5, .position = {-5, 0, 60}, .color = 0xFF00FFFF}
};


uint32_t TraceRay(double *origin, double *destination, double min, double max)
{
	double closest_intersect = DBL_MAX;
	sphere_t *closest_sphere = NULL;

	uint32_t i = 0;

	while (i < sphere_cnt)
	{
		double *intersections = IntersectRaySphere(origin, destination, &spheres[i]);
		if (intersections == NULL)
		{
			printf("no intersect with sphere %u\n", i);
			i++;
			continue;
		}
		printf("a intersect with sphere %u\n", i);
		if (intersections[0] < closest_intersect)
		{
			closest_intersect = intersections[0];
			closest_sphere = &spheres[i];
		}
		if (intersections[1] < closest_intersect)
		{
			closest_intersect = intersections[1];
			closest_sphere = &spheres[i];
		}
		i++;
	}
	if (closest_sphere == NULL)
		return (0xFF000000);
	return (closest_sphere->color);
}

void	render(void)
{
	int	x;
	int	y;
	double origin[3] = {0, 0, 0}; 

	x = -(SCREEN_WIDTH / 2);
	while (x < SCREEN_WIDTH / 2)
	{
		y = -(SCREEN_HEIGHT / 2);
		while (y < SCREEN_HEIGHT / 2)
		{
			double *viewPort = CanvasToViewport(x, y, -20);
			uint32_t color = TraceRay(origin, viewPort, 1, DBL_MAX);
			mlx_put_pixel(g_img, x + (SCREEN_WIDTH / 2), y + (SCREEN_HEIGHT / 2), color);
			y++;
		}
		x++;
	}
}
