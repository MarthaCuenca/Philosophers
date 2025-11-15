/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:38:11 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/17 19:04:10 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_activity(int id, t_shr_data *share, t_activity task)
{
	t_ms	start;
	t_ms	now;

	start = share->st->start;
	now = curr_time(start);
	id += 1;
	if (!share->dy->time_up)
	{
		if (task == FORK)
			printf("%li %i has taken a fork", now, id);
		else if (task == R_FORK)
			printf("%li %i has taken right fork", now, id);
		else if (task == L_FORK)
			printf("%li %i has taken a left fork", now, id);
		else if (task == EAT)
			printf(ANSI_COLOR_GREEN"%li %i is eating"ANSI_COLOR_RESET, now, id);
		else if (task == SLEEP)
			printf("%li %i is sleeping", now, id);
		else if (task == THINK)
			printf("%li %i is thinking", now, id);
	}
	else
		if (task == DIE)
			printf("      %li %i died", now, id);
	printf("\n");
}
