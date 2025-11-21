/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:13:20 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/21 17:04:26 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>

void	leave_hashi(t_id *single, t_shr_data *share, int curr, int next)
{
	pthread_mutex_lock(&share->dy->mutex[HASHI]);
	share->dy->hashi[curr] = TRUE;
	share->dy->hashi[next] = TRUE;
	pthread_mutex_unlock(&share->dy->mutex[HASHI]);
	single->hand[R] = FALSE;
	single->hand[L] = FALSE;
}

void	take_hashi(t_id *single, t_shr_data *share, int curr, int next)
{
	pthread_mutex_lock(&share->dy->mutex[HASHI]);
	share->dy->hashi[curr] = FALSE;
	share->dy->hashi[next] = FALSE;
	pthread_mutex_unlock(&share->dy->mutex[HASHI]);
	single->hand[R] = TRUE;
	single->hand[L] = TRUE;
}

t_bool	pair_of_hashi(t_id *single, t_shr_data *share, int curr, int next)
{
	leave_hashi(single, share, curr, next);
	take_hashi(single, share, curr, next);
	pthread_mutex_lock(&share->dy->mutex[HASHI]);
	if (single->hand[R] == TRUE && single->hand[L] == TRUE)/*Actually it does not function in correct way. In fact check own forks, no shared forks.*/
	{
		pthread_mutex_unlock(&share->dy->mutex[HASHI]);
		print_activity(single->id, share, FORK);
		return (TRUE);
	}
	pthread_mutex_unlock(&share->dy->mutex[HASHI]);
	return (FALSE);
}
