#include "render.h"
#include <math.h>
#include <stdlib.h>

double to_degrees(double radians)
{
	return (radians * (180.0 * M_PI));
}

double to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double screenx_to_modelx(uint32_t x, uint32_t width)
{
	return ((double)x / (width - 1));
}

double screeny_to_modely(uint32_t y, uint32_t height)
{
	return (1 - ((double)y / (height - 1)));
}

double random_double(void)
{
	return ((double)rand() / (double)RAND_MAX);
}
