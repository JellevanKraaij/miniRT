#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include "render.h"
#include "hittables/sphere.h"
#include "hittables/array.h"
#include "hittables/plane.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

typedef struct s_hook_data
{
	mlx_t	*mlx;
	t_render_params *render_params;
	mlx_image_t *image;
	bool render;
}	t_hook_data;

void	loophook(void *data)
{
	t_hook_data *hook_data = data;
	if (hook_data->render)
	{
		render(hook_data->render_params);
		hook_data->render = false;
	}
}

void	resizehook(int width, int height, void *data)
{
	t_hook_data *hook_data = data;
	hook_data->render_params->width = width;
	hook_data->render_params->height = height;
	mlx_resize_image(hook_data->image, width, height);
	hook_data->render_params->camera = camera_new(vec3_new(1, 0, -1), vec3_new(0, 0, 1), (double)hook_data->render_params->width / (double)hook_data->render_params->height, 70);
	hook_data->render = true;
}

void	keyhook(mlx_key_data_t key, void *data)
{
	t_hook_data *hook_data = data;

	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(hook_data->mlx);
}

int putpixel_f(uint32_t x, uint32_t y, uint32_t color, void *data)
{
	mlx_image_t	*img;

	img = data;
	mlx_put_pixel(img, x, y, color);
	return (0);
}

t_render_params	*sample_config(mlx_image_t *img)
{
	t_render_params *render_params = render_params_new();

	render_params->width = SCREEN_WIDTH;
	render_params->height = SCREEN_HEIGHT;
	render_params->camera = camera_new(vec3_new(1, 0, -1), vec3_new(0, 0, 1), (double)render_params->width / (double)render_params->height, 70);
	render_params->light = light_new(vec3_new(-2, 0, 0), vec3_new(1, 1, 1), 0.8);
	render_params->ambient_light = vec3_scalar_c(vec3_new(1, 1, 1), 0.2);
	render_params->hittables = hittable_array_new(2); //TODO: protect null

	hittable_array_append(&render_params->hittables, hittable_new(vec3_new(0, 0, 5), (t_vec3){}, vec3_new(0, 0, 1), 10, sphere_new(1)));
	hittable_array_append(&render_params->hittables, hittable_new(vec3_new(0, 0.3, 3), (t_vec3){}, vec3_new(0.8, 0, 0), 10, sphere_new(0.3)));
	hittable_array_append(&render_params->hittables, hittable_new(vec3_new(0, 0, 10), vec3_new(0, 0, 1), vec3_new(0, 0.6, 0), 20, plane_new())); //TODO: protect null
	
	// hittable_array_append(&render_params->hittables, hittable_new(vec3_new(0, -10, 0), vec3_new(0, -1, 0), vec3_new(0, 0.8, 0.8), 10, plane_new())); //TODO: protect null

	render_params->putpixel_f = putpixel_f;
	render_params->putpixel_data = img;
	return (render_params);
}

int32_t	main(void)
{
	mlx_t	*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(mlx, img, 0, 0);
	t_hook_data hook_data = {mlx, sample_config(img), img, true};
	mlx_key_hook(mlx, keyhook, &hook_data);
	mlx_resize_hook(mlx, resizehook, &hook_data);
	mlx_loop_hook(mlx, loophook, &hook_data);
	mlx_loop(mlx);
	render_params_destroy(hook_data.render_params);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
