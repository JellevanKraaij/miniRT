#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "matrix.h"

typedef	t_mat t_vec3;
typedef	t_mat t_mat3;

bool mat_is_vec3(const t_mat *matrix);
bool mat_is_mat3(const t_mat *matrix);

t_vec3	*mat_vec3_new(void);
t_vec3	*mat_vec3_new_set(const MAT_TYPE *arr);
t_mat3	*mat_mat3_new(void);

int	mat_vec3_set(t_vec3 *vec, const MAT_TYPE *arr);

MAT_TYPE mat_vec3_dot(const t_vec3 *vec1, const t_vec3 *vec2);

#endif
