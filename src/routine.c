/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/10 09:59:07 by mcuenca-         ###   ########.fr       */
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

t_bool	pair_of_hashi(t_id *single, t_data *share)
{
	int				id[3];

	pthread_mutex_lock(&share->mutex);
	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->people - 1)
		id[NEXT] = 0;
	if (share->hashi[id[CURR]] == TRUE)
	{
		share->hashi[id[CURR]] = FALSE;
		single->owned[0] = TRUE;
	}
	if (share->hashi[id[NEXT]] == TRUE)
	{
		share->hashi[id[NEXT]] = FALSE;
		single->owned[1] = TRUE;
	}
	pthread_mutex_unlock(&share->mutex);
	if (single->owned[0] == TRUE && single->owned[1] == TRUE)
		return (printf("timestamp_in_ms %i has taken a fork\n", single->id), TRUE);
	return (FALSE);
}

void	eat(t_id *single, t_data *share)
{
	int	t;
	int	id[3];

	id[CURR] = single->id;
	id[NEXT] = single->id + 1;
	if (id[NEXT] > share->people)
		id[NEXT] = 0;
	t = 0;
	while (t < share->eat)
		t++;
	pthread_mutex_lock(&share->mutex);
	share->hashi[id[CURR]] = TRUE;
	single->owned[0] = FALSE;
	pthread_mutex_unlock(&share->mutex);
	pthread_mutex_lock(&share->mutex);
	share->hashi[id[NEXT]] = TRUE;
	single->owned[1] = FALSE;
	pthread_mutex_unlock(&share->mutex);
}

void	dream(t_id *single, t_data *share)
{
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
	while (pair_of_hashi(single, share) == FALSE)
		think();/*During x time I check after some time*/
				/*I have to check if philo is alive*/
	eat(single, share);
	/*I have to check if philo is alive*/
	dream(single, share);
	/*I have to check if philo is alive*/
	return (NULL);
}
