/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:17:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/01 18:44:49 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*t_s;
	unsigned char	t_c;

	index = 0;
	t_s = (unsigned char *)s;
	t_c = (unsigned char)c;
	if (n == 0)
		return (((void *)t_s));
	while (index < n)
	{
		t_s[index] = t_c;
		index++;
	}
	return ((void *)t_s);
}

void	*ft_memset_color(void *s, uint32_t color, size_t n)
{
	size_t		i;
	uint32_t	*tmp;

	if (n == 0)
		return (NULL);
	i = (n / sizeof(uint32_t)) + 1;
	tmp = (uint32_t *)s;
	while (i-- > 0)
		*tmp++ = color;
	return (tmp);
}
