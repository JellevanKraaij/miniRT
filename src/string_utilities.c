/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:47:14 by bde-meij          #+#    #+#             */
/*   Updated: 2023/02/16 18:47:17 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

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
