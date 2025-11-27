/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:38:26 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/27 13:41:45 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <unistd.h>
#include <pthread.h>

void	add_meal(t_id *single, t_sh *share)
{
	pthread_mutex_lock(&share->mutex[MEALS]);
	share->meals_counter++;
	single->feed++;
	pthread_mutex_unlock(&share->mutex[MEALS]);
}

void	write_last_meal(t_id *single, t_sh *share)
{
	t_ms	now;

	now = curr_time();
	pthread_mutex_lock(&share->mutex[TIMER]);
	single->last_meal = now;
	pthread_mutex_unlock(&share->mutex[TIMER]);
}

void	eat(t_id *single, t_sh *share)
{
	int	h1;
	int	h2;

	if (single->id == share->people - 1)
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	else
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	if (!take_hashi(single, share, h1, h2))
		return ;
	print_activity(share, single->id, EAT);
	ft_ms_usleep(share->eat);
	leave_hashi(share, h1, h2);
	add_meal(single, share);
}

t_bool	check_own_full(t_id *single, t_sh *share)
{
	t_bool	result;

	result = FALSE;
	pthread_mutex_lock(&share->mutex[FULL]);
	if (share->meals > 0 && single->feed >= share->meals)
		result = TRUE;
	pthread_mutex_unlock(&share->mutex[FULL]);
	return (result);
}
