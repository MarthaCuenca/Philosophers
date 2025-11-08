/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/08 14:35:40 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>

void	*routine_mng(void *data)
{
	int				i;
	t_data			*timer;
	pthread_mutex_t mutex;

	
	i = 1;
	timer = (t_data *)data;
	pthread_mutex_init(&mutex, NULL);
	while (timer->shared_data <= 1000)
	{
		pthread_mutex_lock(&mutex);
		printf("%i\n", timer->shared_data++);
		pthread_mutex_unlock(&mutex);
	
	}
	//think();
	//eat();
	//dream();
	pthread_mutex_destroy(&mutex);
	return (NULL);
}
