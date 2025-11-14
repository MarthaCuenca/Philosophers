/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:48:09 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/14 14:42:44 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void	*watchman(void *data)
{
	/*int			i;
	t_ms		now;
	t_shr_data	*share;

	share = (t_shr_data *)data;
	while (share->dy->time_up == FALSE)
	{
		now = curr_time();
		i = 0;
		while (i < share->st->people)
		{
			if ((now - share->dy->timer[i]) > share->st->death)
			{
				pthread_mutex_lock(&share->dy->mutex);	
				share->dy->time_up = TRUE;
				printf("      %li %i died\n", curr_time(), i);
				pthread_mutex_unlock(&share->dy->mutex);
				return (NULL);
			}
			i++;
		}
		usleep(100);
		//pthread_mutex_unlock(&share->dy->mutex);	
	}
	return (NULL);*/
	int			i;
	t_shr_data	*share;

	share = (t_shr_data *)data;
	i = 0;
	while (i < share->st->people)
		i++;
	return (NULL);
}

t_bool	monitoring_mng(pthread_t *monitor, t_shr_data *share)
{
	if (pthread_create(monitor, NULL, watchman, share))
		return (FALSE);
	return (TRUE);
}
