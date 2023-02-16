/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filmset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:45:20 by bde-meij          #+#    #+#             */
/*   Updated: 2023/02/16 18:45:23 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	check_ambient(char **str)
{
	if (count_array(str) != 3)
		error_messages(3);
	check_value_range(str[1], 0, 1);
	check_value_range(str[2], 0, 255);
	printf("can make ambient\n");
}

void	check_camera(char **str)
{
	if (count_array(str) != 4)
		error_messages(3);
	check_value_range(str[2], -1, 1);
	check_value_range(str[3], 0, 180);
	printf("can make camera\n");
}

void	check_light(char **str)
{
	if (count_array(str) != 4)
		error_messages(3);
	check_value_range(str[2], 0, 1);
	check_value_range(str[3], 0, 255);
	printf("can make light\n");
}
