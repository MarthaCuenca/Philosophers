/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:29:57 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/14 14:53:15 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

/*void	clean_mng(t_id *data, pthread_t *philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->share->st->people)
		pthread_join(philos[i++], NULL);
	pthread_join(*monitor, NULL);
	pthread_mutex_destroy(&data->share->dy->mutex);
	free(data->share->dy->hashi);
	free(data->share->dy->timer);
	free(data);
	free(philos);
}*/

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

t_bool	are_unsign(char **argv, t_no_mod *st)
{
	st->people = ft_atoi(argv[1]);
	if (st->people <= 0)
		return (FALSE);
	st->death = ft_atoi(argv[2]);
	if (st->death <= 0)
		return (FALSE);
	st->eat = ft_atoi(argv[3]);
	if (st->eat <= 0)
		return (FALSE);
	st->rest = ft_atoi(argv[4]);
	if (st->rest <= 0)
		return (FALSE);
	if (argv[5])
	{
		st->times = ft_atoi(argv[5]);
		if (st->times <= 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	are_int(char **argv, t_no_mod *st)
{
	int	j;

	j = 1;
	while (argv[j])
	{
		if (!ft_str_isdigit(argv[j++]))
			return (FALSE);
	}
	if (!are_unsign(argv, st))
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_shr_data		data;
	t_no_mod		st;
	t_mod			dy;
	t_id			*id;

	if (argc < 5 || argc > 6)
		return (1);
	if (!are_int(argv, &st))
		return (1);
	if (!create_share_data(&dy, &st))
		return (1);
	data.st = &st;
	data.dy = &dy;
	data.dy->time_up = FALSE;
	id = get_id_card(data.st->people, &data);
	if (!id)
		return (clean_mng(id, NULL, NULL), 1);
	be_philosopher(id);
	return (0);
}
