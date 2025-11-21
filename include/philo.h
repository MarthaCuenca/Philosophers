/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:13:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/19 20:16:07 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[38;5;229m"//\x1b[33m
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

# define COLOR_BOLD  "\x1b[1m"
# define COLOR_OFF   "\x1b[22m"

# define MAX_INT_CHAR "2147483647"
# define MIN_INT_CHAR "2147483648"
# define MAX_INT 2147483647
# define MIN_INT 2147483648

# include <stdlib.h>
# include <pthread.h>

/*** ** STUCTS * ***/

typedef long	t_ms;

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

typedef enum e_pr_crr_nx
{
	PREV = 0,
	CURR,
	NEXT,
}	t_pr_crr_nx;

typedef enum e_activity
{
	FORK = 0,
	R_FORK,
	L_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
	ALL_FULL
}	t_activity;

typedef enum e_mutex
{
	HASHI = 0,
	T_UP,
	MEALS,
	TIMER,
	PRINT
}	t_mutex;

typedef struct s_mod
{
	t_bool			*hashi;
	t_bool			time_up;
	int				meals;
	t_ms			*timer;
	pthread_mutex_t	mutex[5];
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

typedef struct s_shr_data
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
t_bool			create_share_data(t_mod *dy, t_no_mod *st);
t_bool			*create_hashi(t_no_mod *st);
t_ms			*create_timer(t_no_mod *st);
t_id			*get_id_card(int n, t_shr_data *share);
void			be_philosopher(t_id *data);
void			*routine_mng(void *data);
t_bool			pair_of_hashi(t_id *single, t_shr_data *share, int curr, int next);
void			leave_hashi(t_id *single, t_shr_data *share, 
					int curr, int next);
t_bool			monitoring_mng(pthread_t *monitoring, t_shr_data *share);
t_bool			fest_mng(pthread_t *waiter, t_id *id);

/*** ** UTILS ** ***/
void			ft_isspace(const char *str, int *i);
int				ft_isdigit(int c);
int				ft_str_isdigit(const char *str);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *nptr);
void			reset_timer(t_ms start, t_ms *timer, pthread_mutex_t *mutex);
t_ms			curr_time(t_ms start);
unsigned long	ft_conversion(unsigned long long src, int factor, char op);
void			clean_mng(t_id *data, pthread_t *philos, pthread_t *monitor);
void			print_activity(int id, t_shr_data *share, t_activity task);
#endif
