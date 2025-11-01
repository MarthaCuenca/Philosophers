/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:46:54 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/01 18:35:06 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*space;

	if (nmemb <= 0)
		return (NULL);
	else if (nmemb > ULLONG_MAX / size)
		return (NULL);
	space = malloc(nmemb * size);
	if (!space)
		return (NULL);
	ft_bzero(space, nmemb * size);
	return (space);
}

//gnl
/*void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t		i;
	char		*space;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (NULL);
	space = malloc(nmemb * size);
	if (!space)
		return (NULL);
	while (i < nmemb * size)
		space[i++] = '\0';
	return (space);
}*/
