/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:09:33 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/27 12:44:05 by mcuenca-         ###   ########.fr       */
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
		tmp[i].full = FALSE;
		tmp[i].share = *&share;
		i++;
	}
	*id = tmp;
	return (TRUE);
}

t_bool	create_hashis(int n, t_sh *share)
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

t_bool	save_share_dynamic_data(int n, t_sh *share)
{
	if (!create_hashis(n, share))
		return (FALSE);
	share->time_up = FALSE;
	share->meals_counter = 0;
	pthread_mutex_init(&share->mutex[T_UP], NULL);
	pthread_mutex_init(&share->mutex[MEALS], NULL);
	pthread_mutex_init(&share->mutex[PRINT], NULL);
	pthread_mutex_init(&share->mutex[TIMER], NULL);
	pthread_mutex_init(&share->mutex[FULL], NULL);
	return (TRUE);
}

t_bool	save_share_static_data(char **argv, t_sh *share)
{
	share->people = ft_atoi(argv[1]);
	if (share->people == 0)
		return (FALSE);
	share->death = ft_atoi(argv[2]);
	if (share->death == 0)
		return (FALSE);
	share->eat = ft_atoi(argv[3]);
	if (share->eat == 0)
		return (FALSE);
	share->rest = ft_atoi(argv[4]);
	if (share->rest == 0)
		return (FALSE);
	if (argv[5])
	{
		share->meals = ft_atoi(argv[5]);
		if (share->meals == 0)
			return (FALSE);
	}
	else
		share->meals = 0;
	share->total_meals = share->people * share->meals;
	share->start = curr_time();
	return (TRUE);
}
