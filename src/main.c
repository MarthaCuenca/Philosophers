/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:29:57 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/11 10:43:27 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

unsigned long long	ft_conversion(unsigned long long src, int factor, char op)
{
	unsigned long long	target;

	target = 0;
	if (op == '*')
		target = src * factor;
	else if (op == '/')
		target = src / factor;
	return (target);
}

t_bool	*create_hashi(t_no_mod *st)
{
	int		i;
	t_bool *tmp;

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

t_bool	are_int(char **argv, t_no_mod *st)
{
	int	j;

	j = 1;
	while (argv[j])
	{
		if (!ft_str_isdigit(argv[j++]))
			return (FALSE);
	}
	st->people = ft_atoi(argv[1]);
	st->death = ft_atoi(argv[2]);
	st->eat = ft_atoi(argv[3]);
	st->rest = ft_atoi(argv[4]);
	if (argv[5])
		st->times = ft_atoi(argv[5]);
	return (TRUE);
}

/*pillo el timepo al inicio
//pillo el tiempo cuando empiece a comer
//covierto de um a ml
//resto el tiempo*/
int	main(int argc, char **argv)
{
	t_shr_data		data;
	t_no_mod		st;
	t_mod			dy;
	struct timeval	us;

	if (argc < 5 || argc > 6)
		return (1);
	if (!are_int(argv, &st))
		return (1);
	if (gettimeofday(&us, NULL))
		return (1);
	st.start = ft_conversion(us.tv_usec, 1000, '/');
	dy.hashi = create_hashi(&st);
	if (!dy.hashi)
		return (1);
	data.st = &st;
	data.dy = &dy;
	be_philosopher(data.st->people, &data, routine_mng);
	return (0);
}
