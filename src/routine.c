/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/15 17:21:27 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

t_ms	curr_time(void)
{
	t_ms			ms;
	struct timeval	us;

	if (gettimeofday(&us, NULL))
		return (0);
	ms = ft_conversion(us.tv_usec, 1000, '/');
	return (ms);
}

void	think(void)
{
	usleep(20);
}

void	leave_hashi(t_id *single, t_shr_data *share, int curr, int next)
{
	single->hand[R] = FALSE;
	single->hand[L] = FALSE;
	pthread_mutex_lock(&share->dy->mutex);
	share->dy->hashi[curr] = TRUE;
	share->dy->hashi[next] = TRUE;
	pthread_mutex_unlock(&share->dy->mutex);
}

void	take_hashi(t_id *single, t_shr_data *share, int curr, int next)
{
	single->hand[R] = TRUE;
	single->hand[L] = TRUE;
	pthread_mutex_lock(&share->dy->mutex);
	share->dy->hashi[curr] = FALSE;
	share->dy->hashi[next] = FALSE;
	pthread_mutex_unlock(&share->dy->mutex);
}

t_bool	pair_of_hashi(t_id *single, t_shr_data *share)
{
	int				id[3];

	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->st->people - 1)
		id[NEXT] = 0;
	leave_hashi(single, share, id[CURR], id[NEXT]);
	take_hashi(single, share, id[CURR], id[NEXT]);
	if (single->hand[R] == TRUE && single->hand[L] == TRUE)
	{
		pthread_mutex_lock(&share->dy->mutex);
		printf("%li %i has taken a fork\n", curr_time(), single->id);
		pthread_mutex_unlock(&share->dy->mutex);
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
	single->hand[R] = FALSE;
	single->hand[L] = FALSE;
	pthread_mutex_lock(&share->dy->mutex);
	share->dy->timer[single->id] = curr_time();
	printf("%li %i is eating\n", curr_time(), single->id);
	share->dy->hashi[id[CURR]] = TRUE;
	share->dy->hashi[id[NEXT]] = TRUE;
	pthread_mutex_unlock(&share->dy->mutex);
}

void	dream(t_id *single, t_shr_data *share)
{
	pthread_mutex_lock(&share->dy->mutex);
	printf("%li %i is sleeping\n", curr_time(), single->id);
	pthread_mutex_unlock(&share->dy->mutex);
	usleep(ft_conversion(share->st->rest, 1000, '*'));
}

void	*routine_mng(void *data)
{
	t_id		*single;
	t_shr_data	*share;

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	pthread_mutex_lock(&share->dy->mutex);
	share->dy->timer[single->id] = curr_time();
	while (!share->dy->time_up)
	{
		printf("%li %i is thinking\n", curr_time(), single->id);
		pthread_mutex_unlock(&share->dy->mutex);
		while (pair_of_hashi(single, share) == FALSE)
			think();
		eat(single, share);
		dream(single, share);
		pthread_mutex_lock(&share->dy->mutex);
	}
	pthread_mutex_unlock(&share->dy->mutex);
	return (NULL);
}
