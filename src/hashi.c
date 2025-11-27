/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:13:20 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/27 13:23:35 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

/*void	leave_hashi(t_id *single, t_sh *share)
{
	int	h1;
	int	h2;

	if (single->evod == ODD)//single->id == share->people - 1)
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	else
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	pthread_mutex_unlock(&share->h_mtx[h1]);
	pthread_mutex_unlock(&share->h_mtx[h2]);
}

t_bool	take_hashi(t_id *single, t_sh *share)
{
	int	h1;
	int	h2;

	if (single->evod == ODD)//single->id == share->people - 1)
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
	pthread_mutex_lock(&share->h_mtx[h1]);
	print_activity(share, single->id, FORK);
	pthread_mutex_lock(&share->h_mtx[h2]);
	print_activity(share, single->id, FORK);
	return (TRUE);
}*/

t_bool	check_still_alive(t_id *single, t_sh *share)
{
	t_ms	now;
	t_ms	prev;

	if (check_time_up(share))
		return (FALSE);
	now = curr_time();
	pthread_mutex_lock(&share->mutex[TIMER]);
	prev = single->last_meal;
	pthread_mutex_unlock(&share->mutex[TIMER]);
	if ((now - prev) >= share->death)
		return (FALSE);
	return (TRUE);
}

static void	end(t_sh *share, int h1, int h2)
{
	if (h1 != -1)
		pthread_mutex_unlock(&share->h_mtx[h1]);
	if (h2 != -1)
		pthread_mutex_unlock(&share->h_mtx[h2]);
}

void	leave_hashi(t_sh *share, int h1, int h2)
{
	pthread_mutex_unlock(&share->h_mtx[h1]);
	pthread_mutex_unlock(&share->h_mtx[h2]);
}

t_bool	take_hashi(t_id *single, t_sh *share, int h1, int h2)
{
	if (!check_still_alive(single, share))
		return (FALSE);
	pthread_mutex_lock(&share->h_mtx[h1]);
	if (!check_still_alive(single, share))
		return (end(share, h1, -1), FALSE);
	write_last_meal(single, share);
	print_activity(share, single->id, FORK);
	if (!check_still_alive(single, share))
		return (end(share, h1, -1), FALSE);
	pthread_mutex_lock(&share->h_mtx[h2]);
	if (!check_still_alive(single, share))
		return (end(share, h1, h2), FALSE);
	if (check_time_up(share))
		return (end(share, h1, h2), FALSE);
	print_activity(share, single->id, FORK);
	write_last_meal(single, share);
	return (TRUE);
}
