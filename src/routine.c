/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/27 13:57:55 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>

void	think(t_id *single)
{
	print_activity(single->share, single->id, THINK);
}

void	dream(t_id *single, t_sh *share)
{
	print_activity(single->share, single->id, SLEEP);
	ft_ms_usleep(share->rest);
}

void	*routine_mng(void *data)
{
	t_id	*single;
	t_sh	*share;

	single = (t_id *)data;
	share = ((t_id *)data)->share;
	if (single->evod == ODD)
		usleep(1000);
	while (1)
	{
		eat(single, share);
		if (check_time_up(share) || check_own_full(single, share))
			break ;
		dream(single, share);
		if (check_time_up(share))
			break ;
		think(single);
		if (check_time_up(share))
			break ;
	}
	return (NULL);
}
