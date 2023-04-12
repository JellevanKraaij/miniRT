/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:47:14 by bde-meij          #+#    #+#             */
/*   Updated: 2023/04/12 16:26:46 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_vec3	convert_array_to_vector(char *str)
{
	char	**tmp_strs;

	tmp_strs = protec(ft_split(str, ','));
	return(vec3_new(ft_atof(tmp_strs[0]), ft_atof(tmp_strs[1]), \
		ft_atof(tmp_strs[2])));
}

int	check_dot(char *str)
{
	int	i;
	int	dots;

	i = 0;
	dots = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dots++;
		i++;
	}
	return (dots);
}

int	count_array(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i] != NULL)
		i++;
	return (i);
}

void	free_dubarray(char **dubarray)
{
	int	i;

	i = 0;
	while (dubarray[i] != NULL)
	{
		free(dubarray[i]);
		dubarray[i] = NULL;
		i++;
	}
	free(dubarray);
	dubarray = NULL;
}
