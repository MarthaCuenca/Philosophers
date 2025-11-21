/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean_mng.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:58:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 18:18:28 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

void	clean_pthreads(t_shr_data *share, pthread_t *philos, pthread_t *monitor)
{
	int	i;
	int	n;

	i = 0;
	n = share->st->people;
	while (i < n)
		pthread_join(philos[i++], NULL);
	pthread_join(*monitor, NULL);
	pthread_mutex_destroy(&share->dy->mutex[T_UP]);
	pthread_mutex_destroy(&share->dy->mutex[TIMER]);
	pthread_mutex_destroy(&share->dy->mutex[HASHI]);
	pthread_mutex_destroy(&share->dy->mutex[PRINT]);
	pthread_mutex_destroy(&share->dy->mutex[MEALS]);
}

void	clean_mng(t_id *data, pthread_t *philos,
			pthread_t *monitor)
{
	clean_pthreads(data->share, philos, monitor);
	free(data->share->dy->hashi);
	data->share->dy->hashi = NULL;
	free(data->share->dy->timer);
	data->share->dy->timer = NULL;
	free(data);
	data = NULL;
	free(philos);
	philos = NULL;
}
