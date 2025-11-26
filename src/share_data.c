/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:09:33 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 18:21:11 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

t_id	*get_id_card(int people)
{
	int		i;
	t_id	*tmp;

	tmp = malloc(people * sizeof(t_id));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < people)
	{
		tmp[i].id = i;
		tmp[i].hand[R] = i;
		tmp[i].hand[L] = i + 1;
		if (tmp[i].hand[L] > people - 1)
			tmp[i].hand[L] = 0;
		i++;
	}
	return (tmp);
}

t_bool	save_id_data(int people, t_shr_data *share, t_id **id)
{
	int		i;
	t_id	*single;

	single = get_id_card(people);
	if (!single)
		return (FALSE);
	i = 0;
	while (i < people)
	{
		single[i].feed = 0;
		single[i].last_meal = share->st->start;
		single[i].evod = ft_even_odd(i);
		single[i].share = *&share;
		i++;
	}
	*id = single;
	return (TRUE);
}

t_bool	create_hashi(int n, t_mod *dy)
{
	int				i;

	dy->h_mtx = malloc(n * sizeof(pthread_mutex_t));
	if (!dy->h_mtx)
		return (FALSE);
	dy->hashi = malloc(n * sizeof(int));
	if (!dy->hashi)
		return (free(dy->h_mtx), FALSE);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&dy->h_mtx[i], NULL);
		dy->hashi[i] = TRUE;
		i++;
	}
	return (TRUE);
}

void	init_other_mutex(t_mod *dy)
{
	pthread_mutex_init(&dy->mutex[T_UP], NULL);
	pthread_mutex_init(&dy->mutex[MEALS], NULL);
	pthread_mutex_init(&dy->mutex[PRINT], NULL);
	pthread_mutex_init(&dy->mutex[TIMER], NULL);
}

t_bool	save_share_dynamic_data(int n, t_mod *dy)
{
	if (!create_hashi(n, dy))
		return (FALSE);
	dy->time_up = FALSE;
	dy->meals_counter = 0;
	init_other_mutex(dy);
	return (TRUE);
}
