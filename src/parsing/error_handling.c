/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:46:02 by bde-meij          #+#    #+#             */
/*   Updated: 2023/04/19 14:39:45 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static const char	*g_error_messages[] = {
	"Invalid number of arguments",
	"Unusable file, '*.rt' and access rights required",
	"Value is out of range",
	"Cannot identify object",
	"object incomplete",
	"Malloc has failed us",
	"Argument was NULL"
};

void	print_error(t_parse_errors error_code)
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
	if (j < 4)
	{
		ft_dstrfree(dub_array);
		return (1);
	}
	if (dub_array[i][j - 1] != 't' || dub_array[i][j - 2] != 'r' || \
	dub_array[i][j - 3] != '.' || check_dot(dub_array[i]) > 1)
	{
		ft_dstrfree(dub_array);
		return (1);
	}
	ft_dstrfree(dub_array);
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
		{
			ft_dstrfree(dub_array);
			return (1);
		}
		if (ft_atof(dub_array[i]) < min || ft_atof(dub_array[i]) > max)
		{
			ft_dstrfree(dub_array);
			return (1);
		}
		i++;
	}
	ft_dstrfree(dub_array);
	return (0);
}
