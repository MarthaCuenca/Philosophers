/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:48:59 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/01 19:13:10 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			index;
	unsigned char	*uns;

	index = 0;
	uns = (unsigned char *) s;
	ft_memset(s, '\0', n);
}
