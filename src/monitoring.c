/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:48:09 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/18 15:38:53 by mcuenca-         ###   ########.fr       */
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
		pthread_mutex_lock(&share->dy->mutex[TIMER]);
		if ((now - share->dy->timer[i]) > share->st->death)
		{
			pthread_mutex_unlock(&share->dy->mutex[TIMER]);
			
			pthread_mutex_lock(&share->dy->mutex[T_UP]);
			share->dy->time_up = TRUE;
			pthread_mutex_unlock(&share->dy->mutex[T_UP]);
			
			print_activity(i, share, DIE);	
			break ;
		}
		pthread_mutex_unlock(&share->dy->mutex[TIMER]);
		i++;
	}
}

void	*watchman(void *data)
{
	t_shr_data	*share;

	share = (t_shr_data *)data;
	pthread_mutex_lock(&share->dy->mutex[T_UP]);
	while (!share->dy->time_up)
	{
		pthread_mutex_unlock(&share->dy->mutex[T_UP]);
		is_alive(share);
		usleep(100);
		pthread_mutex_lock(&share->dy->mutex[T_UP]);
	}
	pthread_mutex_unlock(&share->dy->mutex[T_UP]);
	return (NULL);
}

t_bool	monitoring_mng(pthread_t *monitor, t_shr_data *share)
{
	if (pthread_create(monitor, NULL, watchman, share))
		return (FALSE);
	return (TRUE);
}
