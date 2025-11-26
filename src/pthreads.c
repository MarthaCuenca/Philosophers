/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:57:53 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 19:42:56 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

pthread_t	*create_philosophers(int n)//AQUI ALGO
{
	pthread_t	*tmp;

	tmp = malloc(n * sizeof(pthread_t));
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_bool	init_philosophers(t_id *id, pthread_t *philos)
{
	int	i;
	int	people;

	i = 0;
	people = id->share->people;
	while (i < people)
	{
		if (pthread_create(&philos[i], NULL, routine_mng, &id[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	be_philosopher(t_id *id, pthread_t *philos)
{
	if (!init_philosophers(id, philos))
		return (clean_mng(id, philos));
	watchman(id);
	clean_mng(id, philos);
}
