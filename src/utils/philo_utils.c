/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:01:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 20:04:08 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>

void	reset_timer(t_ms start, t_ms *timer, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(&mutex[TIMER]);
	*timer = curr_time(start);
	pthread_mutex_unlock(&mutex[TIMER]);
}

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

t_ms	curr_time(t_ms start)
{
	t_ms			us_to_ms;
	t_ms			s_to_ms;
	t_ms			ms;
	struct timeval	us;

	if (gettimeofday(&us, NULL))
		return (0);
	s_to_ms = ft_conversion(us.tv_sec, 1000, '*');
	us_to_ms = ft_conversion(us.tv_usec, 1000, '/');
	ms = (s_to_ms + us_to_ms) - start;
	return (ms);
}
