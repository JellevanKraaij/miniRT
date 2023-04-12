/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:46:02 by bde-meij          #+#    #+#             */
/*   Updated: 2023/04/12 17:35:47 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static const char	*g_error_messages[] = {
	"Invalid number of arguments",
	"Unusable file, '*.rt' and access rights required",
	"Value is out of range",
	"Cannot identify object",
	"Malloc has failed us"
};

void	print_error(int error_code)
{
	printf("%s\n", g_error_messages[error_code]);
}

void	*protec(void *ptr)
{
	if (ptr == NULL)
	{
		print_error(malloc_er);
		exit(malloc_er);
	}
	return (ptr);
}

int	check_file(char *file_name)
{
	int		i;
	int		j;
	char	**dub_array;

	i = 0;
	dub_array = protec(ft_split(file_name, '/'));
	while (dub_array[i])
		i++;
	i--;
	j = ft_strlen(dub_array[i]);
	if (dub_array[i][j - 1] != 't' || dub_array[i][j - 2] != 'r' || \
	dub_array[i][j - 3] != '.' || j < 4 || check_dot(dub_array[i]) > 1)
	{
		free_dubarray(dub_array);
		return (1);
	}
	free_dubarray(dub_array);
	return (0);
}

int	checkiftof(char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || \
		(str[i] == '-' && i == 0))
		i++;
	if (i != ft_strlen(str) || check_dot(str) > 1)
		return (1);
	return (0);
}

int	check_value_range(char *str, double min, double max)
{
	char	**dub_array;
	int		i;
	int		j;

	dub_array = protec(ft_split(str, ','));
	i = 0;
	j = count_array(dub_array);
	while (i < j)
	{
		if (checkiftof(dub_array[i]))
			return (1);
		if (ft_atof(dub_array[i]) < min || ft_atof(dub_array[i]) > max)
			return (1);
		i++;
	}
	free_dubarray(dub_array);
	return (0);
}
