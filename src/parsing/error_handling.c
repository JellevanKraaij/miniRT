/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:46:02 by bde-meij          #+#    #+#             */
/*   Updated: 2023/02/16 18:46:15 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static const char	*g_error_messages_strings[] = {
	"Invalid number of arguments",
	"Unusable file, '*.rt' and access rights required",
	"Value is out of range",
	"Cannot identify object",
	"Malloc has failed us"
};

void	error_messages(int error_code)
{
	if (error_code > 0 && ((size_t)error_code - 1) < \
	sizeof(g_error_messages_strings) / sizeof(char *))
		printf("Error\n%s\n", g_error_messages_strings[error_code - 1]);
	exit(EXIT_FAILURE);
}

void	*protec(void *ptr)
{
	if (ptr == NULL)
		error_messages(memal);
	return (ptr);
}

void	check_file(char *file_name)
{
	int		i;
	char	**dub_array;

	i = ft_strlen(file_name);
	dub_array = protec(ft_split(file_name, '.'));
	if ((i < 4) || (count_array(dub_array) != 2))
		error_messages(wrongfile);
	if (ft_strlen(dub_array[1]) != 2 || dub_array[1][0] != 'r' || \
		dub_array[1][1] != 't')
		error_messages(wrongfile);
	free_dubarray(dub_array);
}

char	*checkiftof(char *str)
{
	size_t	i;
	int		dots;

	i = 0;
	dots = 0;
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || \
	(str[i] == '-' && i == 0) || str[i] == '\n')
	{
		if (str[i] == '.')
			dots++;
		i++;
	}
	if (i != ft_strlen(str) || dots > 1)
		error_messages(outofrange);
	return (str);
}

void	check_value_range(char *str, double min, double max)
{
	char	**dub_array;
	int		i;
	int		j;

	dub_array = protec(ft_split(str, ','));
	i = 0;
	j = count_array(dub_array);
	while (i < j)
	{
		if (ft_atof(checkiftof(dub_array[i])) < min || \
			ft_atof(checkiftof(dub_array[i])) > max)
			error_messages(outofrange);
		i++;
	}
	free_dubarray(dub_array);
}
