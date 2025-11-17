/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean_mng.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:58:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/17 19:01:37 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

void	wait_pthreads(int n, pthread_t *philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	if (philos)
		while (i < n)
			pthread_join(philos[i++], NULL);
	if (monitor)
		pthread_join(*monitor, NULL);
}

void	clean_mng(t_id *data, pthread_t *philos, pthread_t *monitor)
{
	if (philos || monitor)
	{
		wait_pthreads(data->share->st->people, philos, monitor);
		pthread_mutex_destroy(&data->share->dy->mutex);
	}
	free(data->share->dy->hashi);
	data->share->dy->hashi = NULL;
	free(data->share->dy->timer);
	data->share->dy->timer = NULL;
	free(data);
	data = NULL;
	free(philos);
	philos = NULL;
}
