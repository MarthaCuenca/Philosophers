/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:17 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/01 18:10:46 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_count_digits(long int n)
{
	int	count;

	if (n > 2147483647 || n < -2147483647)
		return (0);
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	count = 0;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_stmem_itoa(char *dest, int size, long int n)
{
	int	digits;

	if (!dest || size <= 0 || size > 12 || n > 2147483647 || n < -2147483647)
		return (NULL);
	digits = ft_count_digits(n);
	if (n < 0)
	{
		n *= -1;
		dest[0] = '-';
		digits++;
	}
	if (digits >= size)
	{
		dest[0] = '\0';
		return (NULL);
	}
	dest[digits] = '\0';
	while (digits-- > 0)
	{
		dest[digits] = (n % 10) + '0';
		n = n / 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	long int	nlong;
	long int	i;
	char		*c;

	nlong = n;
	i = ft_count_digits(nlong);
	c = ft_calloc(i + 1, sizeof(char));
	if (!c)
		return (NULL);
	if (nlong == 0)
		c[0] = '0';
	if (n < 0)
	{
		c[0] = '-';
		nlong *= -1;
	}
	c[i--] = '\0';
	while (nlong)
	{
		c[i--] = nlong % 10 + '0';
		nlong = nlong / 10;
	}
	return (c);
}
