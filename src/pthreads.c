/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:57:53 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 15:12:36 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

pthread_t	*create_philosophers(int n)
{
	pthread_t	*tmp;

	tmp = malloc(n * sizeof(pthread_t));
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_bool	init_philosophers(t_id *id, t_shr_data *share, pthread_t *philos)
{
	int	i;
	int	n;

	i = 0;
	n = share->st->people;
	while (i < n)
	{
		id[i].share = share;
		id[i].i = 0;
		if (pthread_create(&philos[i], NULL, routine_mng, &id[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	be_philosopher(t_id *id)
{
	pthread_t	monitor;
	pthread_t	*philos;

	pthread_mutex_init(&id->share->dy->mutex[T_UP], NULL);
	pthread_mutex_init(&id->share->dy->mutex[TIMER], NULL);
	pthread_mutex_init(&id->share->dy->mutex[HASHI], NULL);
	pthread_mutex_init(&id->share->dy->mutex[PRINT], NULL);
	if (!monitoring_mng(&monitor, id->share))
		return (clean_mng(id, NULL, NULL));
	philos = create_philosophers(id->share->st->people);
	if (!philos)
		return (clean_mng(id, NULL, NULL));
	if (!init_philosophers(id, id->share, philos))
		return (clean_mng(id, philos, &monitor));
	clean_mng(id, philos, &monitor);
}
