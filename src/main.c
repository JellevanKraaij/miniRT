#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h> //sqrt() pow() hypot()
#define WIDTH 512
#define HEIGHT 512
#define VIEWPORT_WIDTH 10
#define VIEWPORT_HEIGHT 10

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

typedef struct sphere_struct
{
	double center[3];
	double radius;
	unsigned colour;
}	t_sphere ;



double *abc_formula(a, b, c)
{
	double joep = (b * b - (4 * a * c));
	if (joep < 0)
		return (NULL);
	double *hit = malloc(sizeof(double) * 2);
	hit[0] = (-b + sqrt(joep)) / (2 * a);
	hit[1] = (-b - sqrt(joep)) / (2 * a);
	return (hit);
}

double dot(double *a, double *b, int arraysize)
{
	int i = 0;
	double result = 0.0;
	while (i < arraysize)
	{
		result += a[i] * b[i];
		i++;
	}
	// printf("result = %f\n", result);
	return (result);
}

double *intersect(t_sphere ball, double x, double y)
{
	double *D = malloc(sizeof(double) * 3);
	D[0] = x * ((double)VIEWPORT_WIDTH / (double)WIDTH);
	D[1] = y * ((double)VIEWPORT_WIDTH / (double)WIDTH);
	D[2] = -20;
	double r = ball.radius;
	double *hitpoints;
	double *CO;
	CO = ball.center;
	double a = dot(D, D, 3);
	double b = 2 * dot(CO, D, 3);
	double c = dot(CO, CO, 3) - r*r;
	// printf("%f %f %f\n", a, b, c);
	hitpoints = abc_formula(a, b, c);
	// if (hitpoints[0] > 0 || hitpoints[1] > 0)
	// printf("%f and %f\n", hitpoints[0], hitpoints[1]);
	return (hitpoints);
}

unsigned trace_Ray(t_sphere *balls, double x, double y)
{
	double t_max;
	double t_min = 10000;
	int i = 0;
	double *t = malloc(sizeof(double) * 2);
	unsigned colour = 0xFFFF00FF;
	while (i < 3)
	{
		t = intersect(balls[i], x, y);
		if (t != NULL)
		{
			if (t[0] < t_min)
			{
				t_min = t[0];
				colour = balls[i].colour;
			}
			if (t[1] < t_min)
			{
				t_min = t[1];
				colour = balls[i].colour;
			}
		}
			i++;
	}
	return (colour);
}


int32_t	main(void)
{
	mlx_t	*mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	mlx_image_t	*g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	// double x = -WIDTH/2;
	// double y = -HEIGHT/2;
	double x = 0;
	double y = 0;
	unsigned colour;

	t_sphere red_ball;
	red_ball.center[0] = 5;
	red_ball.center[1] = 5;
	red_ball.center[2] = 60;
	red_ball.radius = 4.0;
	red_ball.colour = 0xFF0000FF;
	t_sphere blue_ball;
	blue_ball.center[0] = 0;
	blue_ball.center[1] = 0;
	blue_ball.center[2] = 66;
	blue_ball.radius = 4.0;
	blue_ball.colour = 0x00FF00FF;
	t_sphere green_ball;
	green_ball.center[0] = -5;
	green_ball.center[1] = -5;
	green_ball.center[2] = 60;
	green_ball.radius = 4.0;
	green_ball.colour = 0x0000FFFF;

	t_sphere *balls = malloc(sizeof(t_sphere) * 3);
	balls[0] = red_ball;
	balls[1] = blue_ball;
	balls[2] = green_ball;

	y = -HEIGHT/2;
	while (y < HEIGHT/2)
	{
		x = -WIDTH/2;
		while (x < WIDTH/2)
		{
			colour = trace_Ray(balls, x, y);
			mlx_put_pixel(g_img, x + (WIDTH/2), y + (HEIGHT/2), colour);
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
	return (0);
}


// void draw_sphere()
// {
// 	t_cords camera;
// 	t_cords ray;
// 	int DEPTH = 100;
// 	double x_mid = WIDTH/2;
// 	double y_mid = HEIGHT/2;
// 	double z_mid = DEPTH/2;
// 	double r = 50;
// 	double FOV = 0.75;
// 	double x = WIDTH/2 + 10;
// 	double y = HEIGHT/2 + 10;
// 	double z =  DEPTH/2 + 10;
// 	double *hit_x;
// 	double *hit_y;

// 	// hit_x = abc_formula(pow(z*x, 2), 2*(x - x_mid), -pow(r, 2));
// 	// hit_y = abc_formula(pow(z*y, 2), 2*(y - y_mid), -pow(r, 2));
// 	// printf("%f\n", hit_x[0]);
// 	// printf("%f\n", hit_x[1]);
// 	// printf("%f\n", hit_y[0]);
// 	// printf("%f\n", hit_y[1]);
// 	// if ()
// 	// 	mlx_put_pixel(g_img, x, y, 0xFEDD00FF);
// 	while (x < WIDTH)
// 	{
// 		while (y < HEIGHT)
// 		{
// 			if (trace_Ray == 1)
// 				mlx_put_pixel(g_img, x, y, 0xFEDD00FF);
// 			y++;
// 		}
// 		y = 0
// 		x++;
// 	}
// }

// prequel
// 	O = (0,0,0) camera position
// 	frame, viewport, has width and height, Vw en Vh 
// 	en ligt op afstand 'd' (frameZ - cameraZ)
// 	voor dit voorbeeld is d == 1 (FOV wordt 53% komt door de hoeken van camera naar viewport)

// canvas to viewport
// 	canvas coordinates of the pixel, Cx Cy
// 	dus viewportX = Cx * (Vmax_w / Cmax_w)
// 	dus viewportY = Cy * (Vmax_h / Cmax_h)
// 	viewportZ = d = 1

// Ray equation
// 	ray gaat van camera naar viewport, en P is een punt op de Ray
// 	P = t(V-O) + O
// 	V-O is de richting van de Ray, nu tD

// Sphere equation
// 	we hebben center C en radius r en punten P (nu is P punten op de sphere)
// 	verschil tussen P en C is r, te schrijven als 
// 	(P - C) * (P - C) = r*r

// Ray meet Sphere
// 	we hebben (P - C) * (P - C) = r*r en P = tD + O
// 	de vergelijking wordt (tD+O - C) * (tD+O - C) = r*r
// 	ABCformule maken
// 	O - C = OC dan krijg je (tD + OC) * (tD + OC) = r*r
// 	tD[2] + 2(tD*OC) + OC[2] -r[2]
// 	a = D[2]
// 	b = D*OC
// 	c = OC[2] - r[2]
// 	-b +/- (sqrt(b[2] - 4ac)) / 2a

// nu in code