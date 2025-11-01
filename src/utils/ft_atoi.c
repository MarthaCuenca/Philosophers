/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:42:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/01 19:12:52 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_all(const char *nptr)
{
	int			i;
	long int	num;
	int			mul;

	i = 0;
	num = 0;
	mul = 1;
	if (!nptr || !ft_str_isdigit(nptr))
		exit (EXIT_FAILURE);
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		nptr++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			mul = -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		num = nptr[i++] - '0' + num * 10;
		if ((num * mul) < -2147483648 || (num * mul) > 2147483647)
			exit (EXIT_FAILURE);
	}
	return (mul * num);
}

int	ft_atoi(const char *nptr)
{
	int	index;
	int	num;
	int	mul;

	index = 0;
	num = 0;
	mul = 1;
	while (nptr[index] == 32 || (nptr[index] >= 9 && nptr[index] <= 13))
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			mul = -1;
		index++;
	}
	while (nptr[index] > 47 && nptr[index] < 58)
	{
		num = nptr[index] - '0' + num * 10;
		index++;
	}
	return (mul * num);
}
