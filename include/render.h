#ifndef RENDER_H
# define RENDER_H

#include <stdint.h>

double to_degrees(double radians);
double to_radians(double degrees);
uint32_t	rgb_to_rgba(const uint8_t	color[3]);

#endif
