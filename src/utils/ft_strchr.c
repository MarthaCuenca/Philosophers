/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:59:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/21 20:29:50 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				index;
	char			*t_s;
	unsigned char	t_c;

	index = 0;
	t_s = (char *)s;
	t_c = (unsigned char)c;
	while (t_s[index] != '\0')
	{
		if (t_s[index] == t_c)
			return (&t_s[index]);
		index++;
	}
	if (t_c == '\0')
		return (&t_s[index]);
	return (0);
}

//gnl
/*char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*chr_s;
	unsigned char	un_c;

	i = 0;
	chr_s = (char *)s;
	un_c = (unsigned char)c;
	while (chr_s[i] != '\0')
	{
		if (chr_s[i] == un_c)
			return (&chr_s[i]);
		i++;
	}
	if (chr_s[i] == '\0' && un_c == '\0')
		return (&chr_s[i]);
	return (NULL);
}*/

int	count_c_char(const char *s, int c)
{
	int		i;
	char	*new_s;

	if (!s || !c)
		return (0);
	i = 0;
	new_s = (char *)s;
	while (new_s)
	{
		new_s = ft_strchr(new_s, c);
		if (!new_s)
			break ;
		new_s++;
		i++;
	}
	return (i);
}
