#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>

#include "hooks.h"
#include <fcntl.h>
#include "parse.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define MAX_RAY_PER_PIXEL 100

t_render_params	*sample_config(void)
{
	t_render_params	*render_params;

	render_params = render_params_new();
	render_params->camera = camera_new(vec3_new(0, 0, 0), vec3_new(0, 0, 1), 70);
	render_params->ambient = ambient_new(vec3_new(255, 255, 255), 0.5);
	render_params->light = point_light_new(vec3_new(0, 0, 0), vec3_new(255, 255, 255), 0.7);
	render_params->hittables = hittable_array_new(1);
	hittable_array_append(&render_params->hittables, hittable_new(CIRCLE, material_new(vec3_new(255, 0, 0)), vec3_new(0, 0, 5), vec3_new(0, 0, 1), 0.5));
	return (render_params);
}

void	init_hook_data(t_hook_data *hook_data, mlx_t *mlx, \
t_render_params *render_params, mlx_image_t *img)
{
	hook_data->mlx = mlx;
	hook_data->width = SCREEN_WIDTH;
	hook_data->height = SCREEN_HEIGHT;
	hook_data->render_params = render_params;
	hook_data->image = img;
	hook_data->image_data = NULL;
	hook_data->max_ray_per_pixel = MAX_RAY_PER_PIXEL;
}

void	run_program(mlx_t *mlx, mlx_image_t *img, \
t_render_params *render_params)
{
	t_hook_data		hook_data;

	mlx_image_to_window(mlx, img, 0, 0);
	init_hook_data(&hook_data, mlx, render_params, img);
	mlx_key_hook(mlx, escapehook, &hook_data);
	mlx_resize_hook(mlx, resizehook, &hook_data);
	mlx_loop_hook(mlx, renderhook, &hook_data);
	mlx_loop(mlx);
	render_params_destroy(render_params);
	mlx_terminate(mlx);
}

int32_t	main(int ac, char **av)
{
	// int				fd;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_render_params	*render_params;

	(void)ac;
	(void)av;

	// if (ac != 2)
	// 	return (print_error(N_ARGS_ER), EXIT_FAILURE);
	// if (check_file(av[1]))
	// 	return (print_error(WRONGFILE), EXIT_FAILURE);
	// fd = open(av[1], O_RDONLY);
	// if (fd < 0)
		// return (print_error(WRONGFILE), EXIT_FAILURE);
	// render_params = render_params_new();
	render_params = sample_config();
	// if (check_file_args(fd, render_params))
		// return (EXIT_FAILURE);
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", true);
	img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlx)
		return (EXIT_FAILURE);
	run_program(mlx, img, render_params);
	return (EXIT_SUCCESS);
}
