/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:13:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/11/26 19:35:22 by mcuenca-         ###   ########.fr       */
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

typedef enum e_evod
{
	EVEN = 0,
	ODD = 1
}	t_evod;

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
	PRINT,
	TIMER,
}	t_mutex;

typedef struct s_sh
{
	int				people;
	int				death;
	int				eat;
	int				rest;
	int				meals;
	int				total_meals;
	t_ms			start;
	//
	t_bool			time_up;
	int				meals_counter;
	t_bool			*hashi;
	pthread_mutex_t	*h_mtx;
	pthread_mutex_t	mutex[5];

}	t_sh;

typedef struct s_id
{
	int					id;
	t_evod				evod;
	int					hand[2];
	int					feed;
	t_ms				last_meal;
	struct s_sh			*share;
}	t_id;

/***  FUNCTIONS  ***/
t_bool			save_share_dynamic_data(int n, t_sh *share);
t_bool			save_id_data(int people, t_sh *share, t_id **id);
pthread_t		*create_philosophers(int n);
void			one_philosopher(t_id *id, pthread_t *philos);
void			be_philosopher(t_id *data, pthread_t *philos);
void			*routine_mng(void *data);
void			leave_hashi(t_id *single, t_sh *share);
t_bool			take_hashi(t_id *single, t_sh *share);
void			watchman(t_id *id);
t_bool			is_alive(t_id *single, t_sh *share);
void			write_last_meal(t_id *single, t_sh *share);
t_bool			check_time_up(t_sh *share);
t_bool			check_full(t_sh *share);

/*** ** UTILS ** ***/
void			ft_isspace(const char *str, int *i);
int				ft_isdigit(int c);
int				ft_str_isdigit(const char *str);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *nptr);
int				ft_even_odd(int n);
char			*ft_strchr(const char *s, int c);
void			ft_ms_usleep(int n);
t_ms			curr_time(void);
unsigned long	ft_conversion(unsigned long long src, int factor, char op);
void			clean_mng(t_id *data, pthread_t *philos);
void			print_activity(t_sh *share, int id, t_activity task);
#endif
