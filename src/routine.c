/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/12 18:43:45 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

t_ms	curr_time()
{
	t_ms			ms;
	struct timeval	us;

	if (gettimeofday(&us, NULL))
		return (0);
	ms = ft_conversion(us.tv_usec, 1000, '/');
	return (ms);
}

t_bool	is_alive(t_id *single, t_shr_data *share)
{
	t_ms			chrono;
	t_ms			ms;

	ms = curr_time();
	chrono = ms - single->timer;
	if (chrono > (t_ms)share->st->death || share->dy->time_up == TRUE)
	{
		/*printf("id[%i]:\n", single->id);
		printf("%luus\n", us.tv_usec);
		printf("%luus / 1000 = %lums\n", us.tv_usec, ms);
		printf("start = %dms\n",  single->timer);
		printf("curr = %lums\n", ms);
		printf("%lums - %dms = \n", chrono, single->timer);
		printf("%lu > %i\n", chrono, share->st->death)*/;
		pthread_mutex_lock(&share->dy->mutex);
		printf("      %li %i died\n", curr_time(), single->id);
		pthread_mutex_unlock(&share->dy->mutex);
		return (FALSE);
	}
	single->timer = chrono;
	return (TRUE);
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

	//pthread_mutex_lock(&share->dy->mutex);
	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->st->people - 1)
		id[NEXT] = 0;
	//pthread_mutex_unlock(&share->dy->mutex);
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
	single->timer = curr_time();
	single->hand[R] = FALSE;
	single->hand[L] = FALSE;
	pthread_mutex_lock(&share->dy->mutex);
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
	single->timer = 0;
	usleep(ft_conversion(share->st->rest, 1000, '*'));
}

void	*routine_mng(void *data)
{
	t_id		*single;
	t_shr_data	*share;

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	pthread_mutex_lock(&share->dy->mutex);
	if (share->dy->time_up == TRUE)
		return (NULL);
	printf("%li %i is thinking\n", curr_time(),  single->id);
	pthread_mutex_unlock(&share->dy->mutex);
	/*Previouly than become routine loop threads have to stop when philo die*/
	/*Parece que he poner la variable que infica muerte como condiciond el bucle*/
	while (pair_of_hashi(single, share) == FALSE)
	{
		think();
		if (share->dy->time_up == TRUE || !is_alive(single, share))
			return (NULL);
	}
	if (share->dy->time_up == TRUE)
		return (NULL);
	eat(single, share);
	if (share->dy->time_up == TRUE || !is_alive(single, share)
		|| (share->st->times != 0 && single->i > share->st->times))
		return (NULL);
	dream(single, share);
	if (share->dy->time_up == TRUE || !is_alive(single, share))
		return (NULL);
	return (NULL);
}
