#ifndef VEC3_H
#define VEC3_H

#ifndef VEC3_TYPE
#define VEC3_TYPE double
#endif

typedef struct s_vec3
{
	VEC3_TYPE	data[3];
}	t_vec3;

t_vec3	vec3_new(const VEC3_TYPE data[3]);

void	vec3_set(t_vec3 *vec, const VEC3_TYPE data[3]);
void	vec3_fill(t_vec3 *vec, const VEC3_TYPE val);


t_vec3	vec3_add(const t_vec3 *lhs, const t_vec3 *rhs);
t_vec3	vec3_add_c(const t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_subtract(const t_vec3 *lhs, const t_vec3 *rhs);
t_vec3	vec3_subtract_c(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	vec3_multiply(const t_vec3 *lhs, const t_vec3 *rhs);
t_vec3	vec3_multiply_c(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	vec3_scalar(const t_vec3 *lhs, const VEC3_TYPE rhs);
t_vec3	vec3_scalar_c(const t_vec3 lhs, const VEC3_TYPE rhs);

VEC3_TYPE	vec3_dot(const t_vec3 *lhs, const t_vec3 *rhs);
VEC3_TYPE	vec3_dot_c(const t_vec3 lhs, const t_vec3 rhs);

void 	vec3_print(const t_vec3 *vec);


#endif
