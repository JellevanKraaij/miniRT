#ifndef CAMERA_H
#define CAMERA_H

#include <vec3.h>
#include <ray.h>

typedef struct s_camera
{
	// Initial definition of camera
	t_vec3	position;
	t_vec3	direction;
	double  aspect_ratio;
	double  hfov;

	// Derived values
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3 	lower_left_corner;
} t_camera;

t_camera *camera_new(const t_vec3 position, const t_vec3 direction, double aspect_ratio, double hfov);

void camera_destroy(t_camera *camera);

void camera_prepare(t_camera *camera);

void camera_update(t_camera *camera, const t_vec3 position, const t_vec3 direction, double aspect_ratio, double hfov);

t_ray camera_generate_ray(const t_camera *camera, double width_pct, double height_pct);

#endif
