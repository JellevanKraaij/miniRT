#ifndef CAMERA_H
#define CAMERA_H

#include <matrix3d.h>
#include <ray.h>

typedef struct s_camera
{
	t_vec3	*origin;
	t_vec3	*horizontal;
	t_vec3	*vertical;
	t_vec3 	*lower_left_corner;
} t_camera;

t_camera *camera_new(const t_vec3 *origin, double aspect_ratio, int hfov);
void camera_destroy(t_camera *camera);

t_ray *camera_generate_ray(const t_camera *camera, double width_pct, double height_pct);

#endif
