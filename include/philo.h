/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:13:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/01 19:14:09 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_INT_CHAR "2147483647"
# define MIN_INT_CHAR "2147483648"
# define MAX_INT 2147483647
# define MIN_INT 2147483648

# include <stdlib.h>

/*** ** STUCTS * ***/
typedef struct s_timer
{
	int	person;
	int	death;
	int	eat;
	int	sleep;
	int	times;
}	t_timer;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

/***  FUNCTIONS  ***/

/*** ** UTILS ** ***/
void	ft_isspace(const char *str, int *i);
int		ft_isdigit(int c);
int		ft_str_isdigit(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *nptr);
#endif
