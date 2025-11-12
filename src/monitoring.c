/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:48:09 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/12 18:28:47 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

void	*watchman(void *data)
{
	int	tmp;
	t_shr_data *d;

	d = (t_shr_data *)data;
	tmp = d->st->eat + d->st->rest;
	return (NULL);
}

t_bool	monitoring_mng(pthread_t *monitoring, t_shr_data *share)
{
	if (pthread_create(monitoring, NULL, watchman, &share))
		return (FALSE);
	pthread_join(*monitoring, NULL);
	return (TRUE);
}

