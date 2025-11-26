/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:29:57 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 19:38:23 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
	t_sh		share;
	t_id		*id;
	pthread_t	*philos;

	if (!valid_arg_data(argc, argv))
		return (1);
	if (!save_share_static_data(argv, &share))
		return (1);
	if (!save_share_dynamic_data(share.people, &share))
		return (1);
	id = NULL;
	if (!save_id_data(share.people, &share, &id))
		return (1);
	philos = create_philosophers(share.people);
	if (!philos)
		return (clean_mng(id, philos), 1);
	if (share.people > 1)
		be_philosopher(id, philos);
	else
		one_philosopher(id, philos);
	return (0);
}
