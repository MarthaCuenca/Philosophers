/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 19:27:56 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	think(t_id *single)
{
	print_activity(single->share, single->id, THINK);
	if (single->evod == EVEN)
		usleep (50);
}

void	dream(t_id *single, t_shr_data *share)
{
	print_activity(single->share, single->id, SLEEP);
	ft_ms_usleep(share->st->rest);
}

void	add_meal(t_id *single, t_shr_data *share)
{
	pthread_mutex_lock(&share->dy->mutex[MEALS]);
	share->dy->meals_counter++;
	pthread_mutex_unlock(&share->dy->mutex[MEALS]);
	single->feed++;
}

void	write_last_meal(t_id *single, t_shr_data *share)
{
	t_ms	now;

	now = curr_time();
	pthread_mutex_lock(&share->dy->mutex[TIMER]);
	single->last_meal = now;
	pthread_mutex_unlock(&share->dy->mutex[TIMER]);
}

void	eat(t_id *single, t_shr_data *share)
{
	if (!take_hashi(single, share))
		return ;
	print_activity(share, single->id, EAT);
	write_last_meal(single, share);
	ft_ms_usleep(share->st->eat);
	leave_hashi(single, share);
	add_meal(single, share);
}

t_bool	check_own_full(t_id *single, t_shr_data *share)
{
	if (share->st->meals != 0)
	{
		if (single->feed >= share->st->meals)
			return (TRUE);
	}
	return (FALSE);
}

void	*routine_mng(void *data)
{
	t_id		*single;
	t_shr_data	*share;

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	if (single->evod == ODD)
		usleep(50);
	while (1)
	{
		eat(single, share);
		if (check_time_up(share) || check_own_full(single, share))
			break ;
		dream(single, share);
		if (check_time_up(share))
			break ;
		think(single);
		if (check_time_up(share))
			break ;
	}
	return (NULL);
}
