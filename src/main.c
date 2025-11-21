/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:29:57 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/21 17:00:53 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
	data.st->start = curr_time(0);
	data.dy = &dy;
	data.dy->meals = 0;
	data.dy->time_up = FALSE;
	id = get_id_card(data.st->people, &data);
	if (!id)
		return (1);
	be_philosopher(id);
	return (0);
}
