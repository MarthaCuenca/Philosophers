/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:57:53 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/12 17:59:29 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void	clean_mng(t_id *data, pthread_t *philos)
{
	free(data->share->dy->hashi);
	free(data);
	free(philos);
}

t_id	*get_id_card(int n)
{
	int		i;
	t_id	*tmp;

	tmp = malloc(n * sizeof(t_id));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		tmp[i].id = i;
		i++;
	}
	i = 0;
	while (i < n)
	{
		tmp[i].hand[R] = FALSE;
		tmp[i].hand[L] = FALSE;
		i++;
	}
	return (tmp);

}

pthread_t	*create_philosophers(int n)
{
	pthread_t	*tmp;

	tmp = malloc(n * sizeof(pthread_t));
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_bool	meeting(int n, t_id **id, pthread_t **philos)
{
	*philos = create_philosophers(n);
	if (!philos)
		return (FALSE);
	*id = get_id_card(n);
	if (!id)
		return (FALSE);
	return (TRUE);
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
		id[i].timer = share->st->start;
		id[i].i = 0;	
		if (pthread_create(&philos[i], NULL, routine_mng, &id[i]))//&& data->dy->time_up == FALSE) 
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < n)
		pthread_join(philos[i++], NULL);
	return (TRUE);
}

t_bool	be_philosopher(t_shr_data *data)//, void *(routine) (void *))
{
	t_id		*id;
	pthread_t	monitor;
	pthread_t	*philos;

	if (!meeting(data->st->people, &id, &philos))
		return (FALSE);
	pthread_mutex_init(&data->dy->mutex, NULL);
	monitoring_mng(&monitor, data);
	init_philosophers(id, data, philos);
	pthread_mutex_destroy(&data->dy->mutex);
	clean_mng(id, philos);
	return (TRUE);
}
