/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:09:33 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 19:40:56 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

t_bool	save_id_data(int people, t_sh *share, t_id **id)
{
	int		i;
	t_id	*tmp;

	tmp = malloc(people * sizeof(t_id));
	if (!tmp)
		return (FALSE);
	i = 0;
	while (i < people)
	{
		tmp[i].id = i;
		tmp[i].evod = ft_even_odd(i);
		tmp[i].hand[R] = i;
		tmp[i].hand[L] = i + 1;
		if (tmp[i].hand[L] > people - 1)
			tmp[i].hand[L] = 0;
		tmp[i].feed = 0;
		tmp[i].last_meal = share->start;
		tmp[i].share = *&share;
		i++;
	}
	*id = tmp;
	return (TRUE);
}

t_bool	create_hashi(int n, t_sh *share)
{
	int				i;

	share->h_mtx = malloc(n * sizeof(pthread_mutex_t));
	if (!share->h_mtx)
		return (FALSE);
	share->hashi = malloc(n * sizeof(int));
	if (!share->hashi)
		return (free(share->h_mtx), FALSE);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&share->h_mtx[i], NULL);
		share->hashi[i] = TRUE;
		i++;
	}
	return (TRUE);
}

void	init_other_mutex(t_sh *share)
{
	pthread_mutex_init(&share->mutex[T_UP], NULL);
	pthread_mutex_init(&share->mutex[MEALS], NULL);
	pthread_mutex_init(&share->mutex[PRINT], NULL);
	pthread_mutex_init(&share->mutex[TIMER], NULL);
}

t_bool	save_share_dynamic_data(int n, t_sh *share)
{
	if (!create_hashi(n, share))
		return (FALSE);
	share->time_up = FALSE;
	share->meals_counter = 0;
	init_other_mutex(share);
	return (TRUE);
}
