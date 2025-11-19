/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 15:12:31 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	reset_timer(t_ms *timer, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(&mutex[TIMER]);
	*timer = curr_time(0);
	pthread_mutex_unlock(&mutex[TIMER]);
}

void	think(t_id *single, t_shr_data *share)

{
	print_activity(single->id, share, THINK);
	usleep(20);
}

void	leave_hashi(t_id *single, t_shr_data *share, int curr, int next)
{
	pthread_mutex_lock(&share->dy->mutex[HASHI]);
	share->dy->hashi[curr] = TRUE;
	share->dy->hashi[next] = TRUE;
	pthread_mutex_unlock(&share->dy->mutex[HASHI]);
	single->hand[R] = FALSE;
	single->hand[L] = FALSE;
}

void	take_hashi(t_id *single, t_shr_data *share, int curr, int next)
{
	pthread_mutex_lock(&share->dy->mutex[HASHI]);
	share->dy->hashi[curr] = FALSE;
	share->dy->hashi[next] = FALSE;
	pthread_mutex_unlock(&share->dy->mutex[HASHI]);
	single->hand[R] = TRUE;
	single->hand[L] = TRUE;
}

t_bool	pair_of_hashi(t_id *single, t_shr_data *share)
{
	int				id[3];

	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->st->people - 1)
		id[NEXT] = 0;
	//if (id[CURR] == id[NEXT])//GOOD pero no se muere
	//	return (FALSE);
	leave_hashi(single, share, id[CURR], id[NEXT]);
	take_hashi(single, share, id[CURR], id[NEXT]);
	if (single->hand[R] == TRUE && single->hand[L] == TRUE)
	{
		print_activity(single->id, share, FORK);
		return (TRUE);
	}
	return (FALSE);
}

void	eat(t_id *single, t_shr_data *share)
{
	int	id[3];

	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->st->people - 1)
		id[NEXT] = 0;
	usleep(ft_conversion(share->st->eat, 1000, '*'));
	reset_timer(&share->dy->timer[single->id], share->dy->mutex);
	print_activity(single->id, share, EAT);
	pthread_mutex_lock(&share->dy->mutex[HASHI]);
	share->dy->hashi[id[CURR]] = TRUE;
	share->dy->hashi[id[NEXT]] = TRUE;
	pthread_mutex_unlock(&share->dy->mutex[HASHI]);
	single->hand[R] = FALSE;
	single->hand[L] = FALSE;
}

void	dream(t_id *single, t_shr_data *share)
{
	print_activity(single->id, share, SLEEP);
	usleep(ft_conversion(share->st->rest, 1000, '*'));
}

void	*routine_mng(void *data)
{
	t_id		*single;
	t_shr_data	*share;

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	reset_timer(&share->dy->timer[single->id], share->dy->mutex);
	pthread_mutex_lock(&share->dy->mutex[T_UP]);
	while (!share->dy->time_up)
	{
		pthread_mutex_unlock(&share->dy->mutex[T_UP]);
		if (pair_of_hashi(single, share) == TRUE)
		{
			eat(single, share);
			dream(single, share);
			think(single, share);
		}
		single->i++;
		pthread_mutex_lock(&share->dy->mutex[T_UP]);
	}
	pthread_mutex_unlock(&share->dy->mutex[T_UP]);
	return (NULL);
}
