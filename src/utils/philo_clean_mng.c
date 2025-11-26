/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean_mng.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:58:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 18:21:44 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

void	clean_pthreads(t_shr_data *share, pthread_t *philos)
{
	int	i;
	int	people;

	i = 0;
	people = share->st->people;
	while (i < people)
		pthread_join(philos[i++], NULL);
	i = 0;
	while (i < people)
	{
		pthread_mutex_destroy(&share->dy->h_mtx[i]);
		i++;
	}
	pthread_mutex_destroy(&share->dy->mutex[T_UP]);
	pthread_mutex_destroy(&share->dy->mutex[MEALS]);
	pthread_mutex_destroy(&share->dy->mutex[PRINT]);
	pthread_mutex_destroy(&share->dy->mutex[TIMER]);
}

void	clean_mng(t_id *data, pthread_t *philos)
{
	clean_pthreads(data->share, philos);
	free(data->share->dy->h_mtx);
	free(data->share->dy->hashi);
	data->share->dy->hashi = NULL;
	free(data);
	data = NULL;
	free(philos);
	philos = NULL;
}
