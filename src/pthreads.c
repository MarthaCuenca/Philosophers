/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:57:53 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/10 09:23:05 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void	fill_array(int n, t_id single[], t_data *share, t_bool hashi[])
{
	int	i;

	i = 0;
	while (i < n)
	{
		single[i].id = i;
		i++;
	}
	i = 0;
	while (i < n)
		hashi[i++] = TRUE;
	share->hashi = hashi;
}

t_bool	be_philosopher(int n, t_data *data, void *(routine) (void *))
{
	int			i;
	t_bool		hashi[n];
	t_id		id[n];
	pthread_t	philos[n];

	i = 0;
	fill_array(n, id, data, hashi);
	pthread_mutex_init(&data->mutex, NULL);
	while (i < n)
	{
		id[i].share = data;
		if (pthread_create(&philos[i], NULL, routine, &id[i])) /*Routine has to be a loop?*/
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < n)
		pthread_join(philos[i++], NULL);
	pthread_mutex_destroy(&data->mutex);
	return (TRUE);
}
