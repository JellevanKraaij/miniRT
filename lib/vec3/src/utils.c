#include "vec3.h"

#include <stdio.h>
#include <stdint.h>

void vec3_set(t_vec3 *vec, const VEC3_TYPE data[3])
{
	uint8_t	i;

	i = 0;
	while (i < 3)
	{
		vec->data[i] = data[i];
		i++;
	}
}

void vec3_fill(t_vec3 *vec, const VEC3_TYPE val)
{
	uint8_t	i;

	i = 0;
	while (i < 3)
	{
		vec->data[i] = val;
		i++;
	}
}

void 	vec3_print(const t_vec3 *vec)
{
	uint8_t	i;

	i = 0;
	while (i < 3)
	{
		printf("%f ", vec->data[i]);
		return;
	}
	printf("\n");
}
