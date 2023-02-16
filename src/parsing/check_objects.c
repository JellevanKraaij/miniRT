/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:45:31 by bde-meij          #+#    #+#             */
/*   Updated: 2023/02/16 18:45:34 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	check_sphere(char **str)
{
	if (count_array(str) != 4)
		error_messages(3);
	check_value_range(str[3], 0, 255);
	printf("can make sphere\n");
}

void	check_plane(char **str)
{
	if (count_array(str) != 4)
		error_messages(3);
	check_value_range(str[2], -1, 1);
	check_value_range(str[3], 0, 255);
	printf("can make plane\n");
}

void	check_cylinder(char **str)
{
	if (count_array(str) != 6)
		error_messages(3);
	check_value_range(str[2], -1, 1);
	check_value_range(str[5], 0, 255);
	printf("can make cylinder\n");
}
