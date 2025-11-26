/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:01:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/25 15:28:18 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

unsigned long	ft_conversion(unsigned long long src, int factor, char op)
{
	unsigned long long	target;

	target = 0;
	if (op == '*')
		target = src * factor;
	else if (op == '/')
	{
		if (src < (unsigned long long)factor)
			target = src % factor;
		else
			target = src / factor;
	}
	return (target);
}

void	ft_ms_usleep(int n)
{
	usleep((useconds_t)n * 1000);
}

t_ms	curr_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}
