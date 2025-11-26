/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:38:11 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 18:22:17 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_activity_2(t_shr_data *share, int id, t_activity task, t_ms now)
{
	t_bool	time_up;

	time_up = check_time_up(share);
	pthread_mutex_lock(&share->dy->mutex[PRINT]);
	if (!time_up)
	{
		if (task == FORK)
			printf("%li %i has taken a fork\n", now, id);
		else if (task == R_FORK)
			printf("%li %i has taken right fork\n", now, id);
		else if (task == L_FORK)
			printf("%li %i has taken left fork\n", now, id);
		else if (task == EAT)
			printf(ANSI_COLOR_GREEN"%li %i is eating"ANSI_COLOR_RESET"\n", now, id);
		else if (task == SLEEP)
			printf("%li %i is sleeping\n", now, id);
		else if (task == THINK)
			printf("%li %i is thinking\n", now, id);
		else if (task == ALL_FULL)
			printf("*****Fest over, all philosophers has eaten!*****\n");
	}
	else
		if (task == DIE)
			printf("      %li %i died\n", now, id);
	pthread_mutex_unlock(&share->dy->mutex[PRINT]);
}

void	print_activity(t_shr_data *share, int id, t_activity task)
{
	t_ms	now;

	now = curr_time() - share->st->start;
	print_activity_2(share, id + 1, task, now);
}
