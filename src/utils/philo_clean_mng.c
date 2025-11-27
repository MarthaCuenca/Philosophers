/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean_mng.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:58:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 23:11:35 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

void	clean_pthreads(t_sh *share, pthread_t *philos)
{
	int	i;
	int	people;

	i = 0;
	people = share->people;
	while (i < people)
		pthread_join(philos[i++], NULL);
	i = 0;
	while (i < people)
	{
		pthread_mutex_destroy(&share->h_mtx[i]);
		i++;
	}
	pthread_mutex_destroy(&share->mutex[T_UP]);
	pthread_mutex_destroy(&share->mutex[MEALS]);
	pthread_mutex_destroy(&share->mutex[PRINT]);
	pthread_mutex_destroy(&share->mutex[TIMER]);
	pthread_mutex_destroy(&share->mutex[FULL]);
}

void	clean_mng(t_id *data, pthread_t *philos)
{
	clean_pthreads(data->share, philos);
	free(data->share->h_mtx);
	free(data->share->hashi);
	data->share->hashi = NULL;
	free(data);
	data = NULL;
	free(philos);
	philos = NULL;
}
