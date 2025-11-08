/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:29:57 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/08 14:09:01 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

t_bool	are_int(char **argv, t_data *data)
{
	int	j;

	j = 1;
	while (argv[j])
	{
		if (!ft_str_isdigit(argv[j++]))
			return (FALSE);
	}
	data->people = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->times = ft_atoi(argv[5]);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_data				data;
	
	(void)argv;
	if (argc < 5 || argc > 6)
		return (1);
	if (!are_int(argv, &data))
		return (1);
	be_philosopher(&data, routine_mng);
	return (0);
}
