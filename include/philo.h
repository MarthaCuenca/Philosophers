/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:13:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/15 17:16:39 by mcuenca-         ###   ########.fr       */
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

typedef long t_ms;

typedef enum e_hand
{
	R = 0,
	L = 1
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


typedef struct s_mod
{
	t_bool			*hashi;
	t_bool			time_up;
	t_ms			*timer;
	pthread_mutex_t	mutex;
}	t_mod;

typedef struct s_no_mod
{
	int				people;
	int				death;
	int				eat;
	int				rest;
	int				times;
	t_ms			start;
}	t_no_mod;

typedef	struct s_shr_data
{
	struct s_no_mod	*st;
	struct s_mod	*dy;
}	t_shr_data;

typedef struct s_id
{
	int					id;
	t_bool				hand[2];
	int					i;
	struct s_shr_data	*share;
}	t_id;

/***  FUNCTIONS  ***/

void			*routine_mng(void *data);
void			be_philosopher(t_id *data);
t_bool			monitoring_mng(pthread_t *monitoring, t_shr_data *share);

/*** ** UTILS ** ***/
void			ft_isspace(const char *str, int *i);
int				ft_isdigit(int c);
int				ft_str_isdigit(const char *str);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *nptr);
t_ms			curr_time();
unsigned long	ft_conversion(unsigned long long src, int factor, char op);
void			clean_mng(t_id *data, pthread_t *philos, pthread_t *monitor);
void			aru(void *tmp);
#endif
