/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:48:09 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/21 17:00:47 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

t_bool	are_full(int n, t_shr_data *share)
{
	if (share->st->times != 0)
	{
		pthread_mutex_lock(&share->dy->mutex[MEALS]);
		if (share->dy->meals > n)
		{
			pthread_mutex_unlock(&share->dy->mutex[MEALS]);
			return (TRUE);
		}
		pthread_mutex_unlock(&share->dy->mutex[MEALS]);
	}
	return (FALSE);
}

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
			//
			/*pthread_mutex_lock(&share->dy->mutex[PRINT]);
			printf("                    %lu - %lu = %lu > %d\n",
				now, share->dy->timer[i],now - share->dy->timer[i], share->st->death);
			pthread_mutex_unlock(&share->dy->mutex[PRINT]);*/
			//
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
	int			n;

	share = (t_shr_data *)data;
	n = share->st->people * share->st->times;
	pthread_mutex_lock(&share->dy->mutex[T_UP]);
	while (!share->dy->time_up)
	{
		pthread_mutex_unlock(&share->dy->mutex[T_UP]);
		is_alive(share);
		if (are_full(n, share))
		{
			pthread_mutex_lock(&share->dy->mutex[T_UP]);
			break ;
		}
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
