/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:15:17 by faguirre          #+#    #+#             */
/*   Updated: 2025/11/01 17:12:54 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (2048);
	}
	return (0);
}

int	ft_str_isdigit(const char *str)
{
	int	i;

	i = 0;
	ft_isspace(str, &i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!(ft_isdigit(str[i])))
		{
			ft_isspace(str, &i);
			if (str[i])
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}
