/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:09:59 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 19:42:32 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>

void	*alone_routine(void *data)
{
	t_id	*single;
	t_sh	*share;

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	write_last_meal(single, share);
	while (!check_time_up(share))
	{
		pthread_mutex_lock(&share->h_mtx[single->hand[R]]);
		share->hashi[single->hand[R]] = FALSE;
		pthread_mutex_unlock(&share->h_mtx[single->hand[R]]);
		print_activity(share, single->id, FORK);
		ft_ms_usleep(share->death);
	}
	return (NULL);
}

void	one_philosopher(t_id *id, pthread_t *philos)
{
	t_id	*single;
	t_sh	*share;

	single = id;
	share = id->share;
	pthread_mutex_lock(&share->mutex[T_UP]);
	if (pthread_create(philos, NULL, alone_routine, id))
		return (clean_mng(id, philos));
	share->time_up = FALSE;
	pthread_mutex_unlock(&share->mutex[T_UP]);
	while (is_alive(single, share))
		usleep(10);
	clean_mng(id, philos);
}
