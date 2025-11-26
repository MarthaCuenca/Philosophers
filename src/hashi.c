/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:13:20 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 18:17:20 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void	leave_hashi(t_id *single, t_shr_data *share)
{
	int	h1;
	int	h2;

	if (single->id == share->st->people - 1)
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	else
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	pthread_mutex_unlock(&share->dy->h_mtx[h1]);
	pthread_mutex_unlock(&share->dy->h_mtx[h2]);
}

t_bool	take_hashi(t_id *single, t_shr_data *share)
{
	int	h1;
	int	h2;

	if (single->id == share->st->people - 1)
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	else
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	if (check_time_up(share))
		return (FALSE);
	pthread_mutex_lock(&share->dy->h_mtx[h1]);
	print_activity(share, single->id, FORK);
	pthread_mutex_lock(&share->dy->h_mtx[h2]);
	print_activity(share, single->id, FORK);
	return (TRUE);
}
