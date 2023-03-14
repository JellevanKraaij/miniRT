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
