#include "render.h"
#include <math.h>

double to_degrees(double radians)
{
	return (radians * (180.0 * M_PI));
}

double to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

static uint8_t _clamp(double x, uint8_t min, uint8_t max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

// uint32_t	convert_color(const t_vec3 *color)
// {
//     return ((uint8_tcolor->data[0] << 24 | color->data[1] << 16 | color->data[2] << 8 | 0xFF);
// }

uint32_t convert_color(const t_vec3 *color)
{
	return (_clamp(color->data[0], 0, 255) << 24 | _clamp(color->data[1], 0, 255) << 16 | _clamp(color->data[2], 0, 255) << 8 | 0xFF);
}
