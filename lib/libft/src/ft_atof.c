/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:33:38 by bde-meij          #+#    #+#             */
/*   Updated: 2023/04/05 19:39:20 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_atof(const char *str)
{
	int		i;
	int		powa;
	double	sign;
	double	value;

	i = 0;
	powa = 0;
	sign = 1;
	value = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
	{
		if (i > 0)
		{
			// if (powa > 0)
			if ((str[i - 1] == '.') || (powa > 0))
				powa += 1;
		}
		if (str[i] != '.')
			value = value * 10 + (str[i] - 48);
		i++;
	}
	return ((value * sign) / pow(10, powa));
}
