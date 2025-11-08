/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:13:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/08 14:34:47 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_INT_CHAR "2147483647"
# define MIN_INT_CHAR "2147483648"
# define MAX_INT 2147483647
# define MIN_INT 2147483648

# include <stdlib.h>
# include <pthread.h>

/*** ** STUCTS * ***/
typedef struct s_data
{
	int	people;
	int	death;
	int	eat;
	int	sleep;
	int	times;
	int	shared_data;
}	t_data;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

/***  FUNCTIONS  ***/

void    	*routine_mng(void *data);
t_bool		be_philosopher(void *data, void *(routine) (void *));

/*** ** UTILS ** ***/
void		ft_isspace(const char *str, int *i);
int			ft_isdigit(int c);
int			ft_str_isdigit(const char *str);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *nptr);
#endif
