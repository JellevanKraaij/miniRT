#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include "render.h"
#include "hittables/sphere.h"
#include "hittables/array.h"
#include "hittables/plane.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000


void	keyhook(mlx_key_data_t key, void *data)
{
	mlx_t	*mlx;

	mlx = data;
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
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
	render_params->camera = camera_new(vec3_new(-0.3, 0, 0), vec3_new(0, 0, 1), (int)render_params->width / (int)render_params->height, 70);
	render_params->light = light_new(vec3_new(1.5, 0, 1), vec3_new(255, 255, 255), 1);

	render_params->hittables = hittable_array_new(2); //TODO: protect null

	hittable_array_append(&render_params->hittables, hittable_new(vec3_new(0, 0, 4), (t_vec3){}, vec3_new(0, 0, 200), sphere_new(0.5)));
	hittable_array_append(&render_params->hittables, hittable_new(vec3_new(0, 0, 15), vec3_new(0, 0, 1), vec3_new(0, 150, 0), plane_new())); //TODO: protect null
	
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
	mlx_key_hook(mlx, keyhook, mlx);
	t_render_params *render_params = sample_config(img);
	render(render_params);
	render_params_destroy(render_params);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
