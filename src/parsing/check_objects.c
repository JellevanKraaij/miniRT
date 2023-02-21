/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:45:31 by bde-meij          #+#    #+#             */
/*   Updated: 2023/02/21 15:17:39 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	convert_array(char *str, double *converted_array)
{
	char	**tmp_strs;

	tmp_strs = protec(ft_split(str, ','));
	converted_array[0] = ft_atof(tmp_strs[0]);
	converted_array[1] = ft_atof(tmp_strs[1]);
	converted_array[2] = ft_atof(tmp_strs[2]);
	free_dubarray(tmp_strs);
}

// x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// ∗ the sphere diameter: 12.6
// ∗ R,G,B colors in range [0-255]: 10, 0, 255

void	check_sphere(char **str)
{
	t_spheres	new_sphere;
	
	if (count_array(str) != 4)
		error_messages(ident);
	check_value_range(str[3], 0, 255);
	printf("can make sphere\n");
	convert_array(str[1], new_sphere.center);
	new_sphere.diameter = atof(str[2]);
	convert_array(str[3], new_sphere.rgb);
	printf("sphere %f\n", new_sphere.center[0]);
	printf("sphere %f\n", new_sphere.center[1]);
	printf("sphere %f\n", new_sphere.center[2]);
	printf("sphere %f\n", new_sphere.diameter);
	printf("sphere %f\n", new_sphere.rgb[0]);
	printf("sphere %f\n", new_sphere.rgb[1]);
	printf("sphere %f\n", new_sphere.rgb[2]);
}

// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225

void	check_plane(char **str)
{
	t_planes	new_plane;
	
	if (count_array(str) != 4)
		error_messages(ident);
	check_value_range(str[2], -1, 1);
	check_value_range(str[3], 0, 255);
	printf("can make plane\n");
	convert_array(str[1], new_plane.a_point);
	convert_array(str[2], new_plane.plane_vector);
	convert_array(str[3], new_plane.rgb);
	printf("plane %f\n", new_plane.a_point[0]);
	printf("plane %f\n", new_plane.a_point[1]);
	printf("plane %f\n", new_plane.a_point[2]);
	printf("plane %f\n", new_plane.plane_vector[0]);
	printf("plane %f\n", new_plane.plane_vector[1]);
	printf("plane %f\n", new_plane.plane_vector[2]);
	printf("plane %f\n", new_plane.rgb[0]);
	printf("plane %f\n", new_plane.rgb[1]);
	printf("plane %f\n", new_plane.rgb[2]);
}

// x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// ∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ the cylinder diameter: 14.2
// ∗ the cylinder height: 21.42
// ∗ R,G,B colors in range [0,255]: 10, 0, 255

void	check_cylinder(char **str)
{
	t_cylinders	new_cylinder;
	
	if (count_array(str) != 6)
		error_messages(ident);
	check_value_range(str[2], -1, 1);
	check_value_range(str[5], 0, 255);
	printf("can make cylinder\n");
	convert_array(str[1], new_cylinder.center);
	convert_array(str[2], new_cylinder.axis);
	new_cylinder.diameter = atof(str[3]);
	new_cylinder.height = atof(str[4]);
	convert_array(str[5], new_cylinder.rgb);
	printf("cylinder %f\n", new_cylinder.center[0]);
	printf("cylinder %f\n", new_cylinder.center[1]);
	printf("cylinder %f\n", new_cylinder.center[2]);
	printf("cylinder %f\n", new_cylinder.axis[0]);
	printf("cylinder %f\n", new_cylinder.axis[1]);
	printf("cylinder %f\n", new_cylinder.diameter);
	printf("cylinder %f\n", new_cylinder.height);
	printf("cylinder %f\n", new_cylinder.rgb[0]);
	printf("cylinder %f\n", new_cylinder.rgb[1]);
	printf("cylinder %f\n", new_cylinder.rgb[2]);
}
