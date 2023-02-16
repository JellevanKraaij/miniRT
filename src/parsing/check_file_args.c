/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:45:02 by bde-meij          #+#    #+#             */
/*   Updated: 2023/02/16 18:45:04 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static const t_jump_table	g_ptrs_to_checkf[] = {
{.id = "A", .check_function = check_ambient},
{.id = "C", .check_function = check_camera},
{.id = "L", .check_function = check_light},
{.id = "sp", .check_function = check_sphere},
{.id = "pl", .check_function = check_plane},
{.id = "cy", .check_function = check_cylinder}
};

void	loop_to_checkfunction(char **split_line)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(split_line[0], g_ptrs_to_checkf[i].id))
		{
			g_ptrs_to_checkf[i].check_function(split_line);
			break ;
		}
		i++;
	}
	if (i >= 6)
		error_messages(id);
}

void	check_file_args(int fd)
{
	char	**split_line;
	char	*next_line;

	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		split_line = protec(ft_splitset(next_line, " \n"));
		free(next_line);
		if (count_array(split_line) == 0)
		{
			free_dubarray(split_line);
			continue ;
		}
		loop_to_checkfunction(split_line);
		free_dubarray(split_line);
	}
}
