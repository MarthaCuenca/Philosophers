/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:13:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/10 09:48:37 by mcuenca-         ###   ########.fr       */
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

typedef enum e_hand
{
	R = 0,
	L
}	t_hand;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum s_pr_crr_nx
{
	PREV = 0,
	CURR,
	NEXT,
}	t_pr_crr_nx;

typedef struct s_data
{
	int				people;
	int				death;
	int				eat;
	int				rest;
	int				times;
	t_bool			*hashi;
	pthread_mutex_t	mutex;
}	t_data;

typedef struct s_id
{
	int				id;
	t_bool			owned[2];
	int				timer;
	struct s_data	*share;
}	t_id;

/***  FUNCTIONS  ***/

void		*routine_mng(void *data);
t_bool		be_philosopher(int n, t_data *data, void *(routine) (void *));

/*** ** UTILS ** ***/
void		ft_isspace(const char *str, int *i);
int			ft_isdigit(int c);
int			ft_str_isdigit(const char *str);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *nptr);
#endif
