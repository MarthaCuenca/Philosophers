/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 20:21:56 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	eat(t_id *single, t_shr_data *share, int curr, int next)
{
//	int	id[3];
	usleep(ft_conversion(share->st->eat, 1000, '*'));
	leave_hashi(single, share, curr, next);
	reset_timer(share->st->start, &share->dy->timer[single->id], share->dy->mutex);
	print_activity(single->id, share, EAT);
	pthread_mutex_lock(&share->dy->mutex[MEALS]);
	share->dy->meals++;
	pthread_mutex_unlock(&share->dy->mutex[MEALS]);
	single->i++;
}

void	dream(t_id *single, t_shr_data *share)
{
	print_activity(single->id, share, SLEEP);
	usleep(ft_conversion(share->st->rest, 1000, '*'));
}

void	think(t_id *single, t_shr_data *share)
{
	print_activity(single->id, share, THINK);
	usleep(20);
}

void	init_some_data(t_id *single, t_shr_data *share, int *id)
{
	reset_timer(share->st->start, &share->dy->timer[single->id], share->dy->mutex);
	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->st->people - 1)
		id[NEXT] = 0;
}

void	*routine_mng(void *data)
{
	t_id		*single;
	t_shr_data	*share;
	int			id[3];

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	init_some_data(single, share, id);
	pthread_mutex_lock(&share->dy->mutex[T_UP]);
	while (!share->dy->time_up)
	{
		pthread_mutex_unlock(&share->dy->mutex[T_UP]);
		if (pair_of_hashi(single, share, id[CURR], id[NEXT]) == TRUE)
		{
			eat(single, share, id[CURR], id[NEXT]);
			if (share->st->times != 0 && single->i >= share->st->times)
				return (NULL);
			dream(single, share);
			think(single, share);
		}
		pthread_mutex_lock(&share->dy->mutex[T_UP]);
	}
	pthread_mutex_unlock(&share->dy->mutex[T_UP]);
	return (NULL);
}
