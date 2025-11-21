/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:09:33 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 19:09:50 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

t_id	*get_id_card(int n, t_shr_data *share)
{
	int		i;
	t_id	*tmp;

	tmp = malloc(n * sizeof(t_id));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		tmp[i].id = i;
		i++;
	}
	i = 0;
	while (i < n)
	{
		tmp[i].hand[R] = FALSE;
		tmp[i].hand[L] = FALSE;
		tmp[i].share = share;
		i++;
	}
	return (tmp);
}

t_ms	*create_timer(t_no_mod *st)
{
	int		i;
	t_ms	*tmp;

	tmp = malloc(st->people * sizeof(t_ms));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < st->people)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

t_bool	*create_hashi(t_no_mod *st)
{
	int		i;
	t_bool	*tmp;

	tmp = malloc(st->people * sizeof(int));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < st->people)
	{
		tmp[i] = TRUE;
		i++;
	}
	return (tmp);
}

t_bool	create_share_data(t_mod *dy, t_no_mod *st)
{
	dy->hashi = create_hashi(st);
	if (!dy->hashi)
		return (FALSE);
	dy->timer = create_timer(st);
	if (!dy->timer)
		return (free(dy->hashi), FALSE);
	return (TRUE);
}

