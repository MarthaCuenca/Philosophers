/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:38:11 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 19:07:26 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_activity_2(int id, pthread_mutex_t *mutex,
			t_ms now, t_activity task)
{
	pthread_mutex_lock(&mutex[PRINT]);
	if (task == FORK)
		printf("%li %i has taken a fork\n", now, id);
	else if (task == R_FORK)
		printf("%li %i has taken right fork\n", now, id);
	else if (task == L_FORK)
		printf("%li %i has taken a left fork\n", now, id);
	else if (task == EAT)
		printf(ANSI_COLOR_GREEN"%li %i is eating"ANSI_COLOR_RESET"\n", now, id);
	else if (task == SLEEP)
		printf("%li %i is sleeping\n", now, id);
	else if (task == THINK)
		printf("%li %i is thinking\n", now, id);
	else if (task == ALL_FULL)
		printf("*****Fest over, all philosophers has eaten!*****\n");
	pthread_mutex_unlock(&mutex[PRINT]);
}

void	print_activity(int id, t_shr_data *share, t_activity task)
{
	t_ms	start;
	t_ms	now;

	start = share->st->start;
	now = curr_time(start);
	id += 1;
	pthread_mutex_lock(&share->dy->mutex[T_UP]);
	if (!share->dy->time_up)
	{
		pthread_mutex_unlock(&share->dy->mutex[T_UP]);
		print_activity_2(id, share->dy->mutex, now, task);
		pthread_mutex_lock(&share->dy->mutex[T_UP]);
	}
	else
	{
		pthread_mutex_unlock(&share->dy->mutex[T_UP]);
		pthread_mutex_lock(&share->dy->mutex[PRINT]);
		if (task == DIE)
			printf("      %li %i died\n", now, id);
		pthread_mutex_unlock(&share->dy->mutex[PRINT]);
		pthread_mutex_lock(&share->dy->mutex[T_UP]);
	}
	pthread_mutex_unlock(&share->dy->mutex[T_UP]);
}
