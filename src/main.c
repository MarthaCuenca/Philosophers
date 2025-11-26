/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:29:57 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 18:15:07 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

t_bool	save_share_static_data(char **argv, t_no_mod *st)
{
	st->people = ft_atoi(argv[1]);
	if (st->people == 0)
		return (FALSE);
	st->death = ft_atoi(argv[2]);
	if (st->death == 0)
		return (FALSE);
	st->eat = ft_atoi(argv[3]);
	if (st->eat == 0)
		return (FALSE);
	st->rest = ft_atoi(argv[4]);
	if (st->rest == 0)
		return (FALSE);
	if (argv[5])
	{
		st->meals = ft_atoi(argv[5]);
		if (st->meals == 0)
			return (FALSE);
	}
	else
		st->meals = 0;
	st->total_meals = st->people * st->meals;
	st->start = curr_time();
	return (TRUE);
}

t_bool	are_unsign(char **argv)
{
	int		j;
	char	*less;

	j = 1;
	less = NULL;
	while (!less && argv[j])
	{
		less = ft_strchr(argv[j], '-');
		j++;
	}
	if (less)
		return (FALSE);
	return (TRUE);
}

t_bool	are_int(char **argv)
{
	int	j;

	j = 1;
	while (argv[j])
	{
		if (!ft_str_isdigit(argv[j]))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

t_bool	valid_arg_data(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (FALSE);
	if (!are_int(argv))
		return (FALSE);
	if (!are_unsign(argv))
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_shr_data	share;
	t_no_mod	st;
	t_mod		dy;
	t_id		*id;
	pthread_t	*philos;

	if (!valid_arg_data(argc, argv))
		return (1);
	if (!save_share_static_data(argv, &st))
		return (1);
	if (!save_share_dynamic_data(st.people, &dy))
		return (1);
	share.st = &st;
	share.dy = &dy;
	id = NULL;
	if (!save_id_data(share.st->people, &share, &id))
		return (1);
	philos = create_philosophers(id->share->st->people);
	if (!philos)
		return (clean_mng(id, philos), 1);
	if (st.people > 1)
		be_philosopher(id, philos);
	else
		one_philosopher(id, philos);
	return (0);
}
