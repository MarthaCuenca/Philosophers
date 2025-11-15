/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:48:09 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/17 18:57:22 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void	is_alive(t_shr_data *share)
{
	int			i;
	t_ms		now;

	i = 0;
	while (i < share->st->people)
	{
		now = curr_time(share->st->start);
		pthread_mutex_lock(&share->dy->mutex);
		if ((now - share->dy->timer[i]) > share->st->death)
		{
			share->dy->time_up = TRUE;
			pthread_mutex_unlock(&share->dy->mutex);
			print_activity(i, share, DIE);
			break ;
		}
		pthread_mutex_unlock(&share->dy->mutex);
		i++;
	}
}

void	*watchman(void *data)
{
	t_shr_data	*share;

	share = (t_shr_data *)data;
	pthread_mutex_lock(&share->dy->mutex);
	while (!share->dy->time_up)
	{
		pthread_mutex_unlock(&share->dy->mutex);
		is_alive(share);
		usleep(100);
		pthread_mutex_lock(&share->dy->mutex);
	}
	pthread_mutex_unlock(&share->dy->mutex);
	return (NULL);
}

t_bool	monitoring_mng(pthread_t *monitor, t_shr_data *share)
{
	if (pthread_create(monitor, NULL, watchman, share))
		return (FALSE);
	return (TRUE);
}
