/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:48:09 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 19:26:14 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

t_bool	check_full(t_shr_data *share)
{
	if (share->st->meals != 0)
	{
		pthread_mutex_lock(&share->dy->mutex[MEALS]);
		if (share->dy->meals_counter >= share->st->total_meals)
		{
			pthread_mutex_unlock(&share->dy->mutex[MEALS]);
			print_activity(share, 0, ALL_FULL);
			return (TRUE);
		}
		pthread_mutex_unlock(&share->dy->mutex[MEALS]);
	}
	return (FALSE);
}

t_bool	check_time_up(t_shr_data *share)
{
	t_bool	stop;

	pthread_mutex_lock(&share->dy->mutex[T_UP]);
	stop = share->dy->time_up;
	pthread_mutex_unlock(&share->dy->mutex[T_UP]);
	return (stop);
}

void	end(t_shr_data *share)
{
	pthread_mutex_lock(&share->dy->mutex[T_UP]);
	share->dy->time_up = TRUE;
	pthread_mutex_unlock(&share->dy->mutex[T_UP]);
}

t_bool	is_alive(t_id *single, t_shr_data *share)
{
	t_ms	now;
	t_ms	prev;

	now = curr_time();
	pthread_mutex_lock(&share->dy->mutex[TIMER]);
	prev = single->last_meal;
	pthread_mutex_unlock(&share->dy->mutex[TIMER]);
	if ((now - prev) >= share->st->death)
	{
		end(share);
		print_activity(share, single->id, DIE);
		return (FALSE);
	}
	return (TRUE);
}

void	watchman(t_id *id)
{
	int			i;
	t_id		*single;
	t_shr_data	*share;

	single = id;
	share = id->share;
	while (1)
	{
		i = 0;
		while (i < share->st->people)
		{
			if (!is_alive(&single[i], share))
				return ;
			i++;
		}
		if (check_full(share))
			return ;
		usleep(100);
	}
}
