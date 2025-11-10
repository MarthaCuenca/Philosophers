/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/10 12:23:55 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	think(void)
{
	usleep(20);
}

void	leave_hashi(t_id *single, t_data *share, int curr, int next)
{
	pthread_mutex_lock(&share->mutex);
	if (single->hand[R] == TRUE)
	{
		single->hand[R] = FALSE;
		share->hashi[curr] = TRUE;
	}
	else
	{
		single->hand[L] = FALSE;
		share->hashi[next] = TRUE;
	}
	pthread_mutex_unlock(&share->mutex);
}

void	take_hashi(t_id *single, t_data *share, int curr, int next)
{
	pthread_mutex_lock(&share->mutex);
	if (share->hashi[curr] == TRUE)
	{
		share->hashi[curr] = FALSE;
		single->hand[R] = TRUE;
	}
	if (share->hashi[next] == TRUE)
	{
		share->hashi[next] = FALSE;
		single->hand[L] = TRUE;
	}
	pthread_mutex_unlock(&share->mutex);
}

t_bool	pair_of_hashi(t_id *single, t_data *share)
{
	int				id[3];

	pthread_mutex_lock(&share->mutex);
	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->people - 1)
		id[NEXT] = 0;
	pthread_mutex_unlock(&share->mutex);
	leave_hashi(single, share, id[CURR], id[NEXT]);
	take_hashi(single, share, id[CURR], id[NEXT]);
	if (single->hand[R] == TRUE && single->hand[L] == TRUE)
	{
		pthread_mutex_lock(&share->mutex);
		printf("timestamp_in_ms %i has taken a fork\n", single->id);
		pthread_mutex_unlock(&share->mutex);
		return (TRUE);
	}
	return (FALSE);
}

void	eat(t_id *single, t_data *share)
{
	int	t;
	int	id[3];

	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->people - 1)
		id[NEXT] = 0;
	t = 0;
	while (t < share->eat)
		t++;
	pthread_mutex_lock(&share->mutex);
	printf("timestamp_in_ms %i is eating\n", single->id);
	share->hashi[id[CURR]] = TRUE;
	single->hand[R] = FALSE;
	pthread_mutex_unlock(&share->mutex);
	pthread_mutex_lock(&share->mutex);
	share->hashi[id[NEXT]] = TRUE;
	single->hand[L] = FALSE;
	pthread_mutex_unlock(&share->mutex);
}

void	dream(t_id *single, t_data *share)
{
	pthread_mutex_lock(&share->mutex);
	printf("timestamp_in_ms %i is sleeping\n", single->id);
	pthread_mutex_unlock(&share->mutex);
	single->timer = 0;
	while (single->timer < share->rest)
	{
		/* Do not forget to implement starvation time
		 * And while philo is thiking can die.*/
		single->timer++;
	}
}

void	*routine_mng(void *data)
{
	t_id			*single;
	t_data			*share;

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	pthread_mutex_lock(&share->mutex);
	printf("timestamp_in_ms %i is thinking\n", single->id);
	pthread_mutex_unlock(&share->mutex);
	while (pair_of_hashi(single, share) == FALSE)
		think();/*During x time I check after some time*/
				/*I have to check if philo is alive*/
	eat(single, share);
	/*I have to check if philo is alive*/
	dream(single, share);
	/*I have to check if philo is alive*/
	return (NULL);
}
