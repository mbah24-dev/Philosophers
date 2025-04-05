/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:55 by mbah              #+#    #+#             */
/*   Updated: 2025/04/05 00:28:06 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define RESET_COLOR    "\033[0m"
# define COLOR_RED      "\033[31m" 
# define COLOR_GREEN    "\033[32m" 

# define PHILO_MAX_NUMBER 200

/******************** (TYPES) ********************/

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

/******************************************************
*                  STRUCTS DEFINITION                 *
*******************************************************/

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*print_lock;
	t_mutex	*meal_lock;
}			t_mutexes;

typedef struct s_times
{
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	time_to_die;
	size_t	time_of_last_meal;
	size_t	time_at_born;
}			t_times;

typedef struct philo
{
	t_mutexes	mutexes;
	t_times		times;
	t_thread	thread;
	int			id;
	int			meals_eat;
	int			philo_nb;
	int			must_eat;
}				t_philo;

typedef struct s_table
{
	t_mutex	*forks;
	t_philo	*philos;
	t_mutex	print_lock;
	t_mutex	meal_lock;
}			t_table;

/******************************************************
*            INITIALIZE TABLE, PHILOS AND FORKS       *
*******************************************************/

void	init_table(t_table *table, t_philo *philos, t_mutex *forks);
void	init_philos(t_table *table, t_philo *philos, t_mutex *forks, char **av);
void	init_forks(t_table *table, t_mutex *forks, int quantity);

/******************************************************
*                  EXTERNAL FUNCTIONS                 *
*******************************************************/

size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);

/******************************************************
*                  PHILO UTILS FUNCTIONS              *
*******************************************************/

void	an_error_occured(char *err_msg, int exit_status);
void	ft_usleep(size_t to_sleep);
size_t	get_time_now(void);
void	display_action(char *action_msg, t_philo *philo);
void	clean_up(t_table *table, char *err_msg, int nb_forks, int exit_status);

void	ft_putchar(char c);

#endif
