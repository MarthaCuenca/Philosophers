/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:13:20 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 22:42:27 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

/*void	leave_hashi(t_id *single, t_sh *share)
{
	int	h1;
	int	h2;

	if (single->evod == ODD)//single->id == share->people - 1)
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	else
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	pthread_mutex_unlock(&share->h_mtx[h1]);
	pthread_mutex_unlock(&share->h_mtx[h2]);
}

t_bool	take_hashi(t_id *single, t_sh *share)
{
	int	h1;
	int	h2;

	if (single->evod == ODD)//single->id == share->people - 1)
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	else
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	if (check_time_up(share))
		return (FALSE);
	pthread_mutex_lock(&share->h_mtx[h1]);
	print_activity(share, single->id, FORK);
	pthread_mutex_lock(&share->h_mtx[h2]);
	print_activity(share, single->id, FORK);
	return (TRUE);
}*/

t_bool	check_still_alive(t_id *single, t_sh *share)
{
	t_ms	now;
	t_ms	prev;
	if (check_time_up(share))
		return (FALSE);
	now = curr_time();
	pthread_mutex_lock(&share->mutex[TIMER]);
	prev = single->last_meal;
	pthread_mutex_unlock(&share->mutex[TIMER]);
	if ((now - prev) >= share->death)
		return (FALSE);
	return (TRUE);
}
void	leave_hashi(t_id *single, t_sh *share)
{
	int	h1;
	int	h2;
	if (single->id == share->people - 1)
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	else
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	pthread_mutex_unlock(&share->h_mtx[h1]);
	pthread_mutex_unlock(&share->h_mtx[h2]);
}
t_bool	take_hashi(t_id *single, t_sh *share)
{
	int	h1;
	int	h2;
	if (single->id == share->people - 1)
	{
		h1 = single->hand[L];
		h2 = single->hand[R];
	}
	else
	{
		h1 = single->hand[R];
		h2 = single->hand[L];
	}
	//Verifica si está vivo ANTES de intentar tomar palillos
	if (!check_still_alive(single, share))
		return (FALSE);
	//3. Toma el primer palillo (puede bloquearse aquí esperando)
	pthread_mutex_lock(&share->h_mtx[h1]);
	//Verifica si todavía está vivo después de obtener el primer palillo
	if (!check_still_alive(single, share))
	{
		pthread_mutex_unlock(&share->h_mtx[h1]);
		return (FALSE);
	}
	// Actualiza last_meal cuando obtiene el primer palillo para dar más tiempo
	write_last_meal(single, share);
	print_activity(share, single->id, FORK);
	//Verifica otra vez si está vivo después de imprimir el mensaje
	if (!check_still_alive(single, share))
	{
		pthread_mutex_unlock(&share->h_mtx[h1]);
		return (FALSE);
	}
	//Toma el segundo palillo (puede bloquearse aquí esperando)
	pthread_mutex_lock(&share->h_mtx[h2]);
	//Verifica si todavía está vivo después de obtener el segundo palillo
	if (!check_still_alive(single, share))
	{
		// Libera AMBOS palillos antes de salir
		pthread_mutex_unlock(&share->h_mtx[h1]);
		pthread_mutex_unlock(&share->h_mtx[h2]);
		return (FALSE);
	}
	//Verifica si time_up está activado
	if (check_time_up(share))
	{
		pthread_mutex_unlock(&share->h_mtx[h1]);
		pthread_mutex_unlock(&share->h_mtx[h2]);
		return (FALSE);
	}
	print_activity(share, single->id, FORK);
	// Actualiza last_meal inmediatamente después de obtener ambos palillos
	write_last_meal(single, share);
	return (TRUE);
}
