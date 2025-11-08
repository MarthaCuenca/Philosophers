/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:57:53 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/08 14:09:05 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
//antes de crear los philos((threads) tienen que tener su rutina
t_bool	be_philosopher(void *data, void *(routine) (void *))
{
	int				i;
	int				people;	
	pthread_t		*philos;
	//pthread_mutex_t	mutex;

	i = 0;
	people = ((t_data *)data)->people;
	philos = malloc((people + 1) * sizeof(pthread_t));
	if (!philos)
		return (FALSE);
	while (i < people)
	{
		if (pthread_create(&philos[i], NULL, routine, data))
			return (FALSE);
		pthread_join(philos[i], NULL);
		i++;
	}
	i = 0;
	free(philos);
	return (TRUE);
}
