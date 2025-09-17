/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:55 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 18:23:14 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

# define MAX_PHILO_NUM        200
# define MAX_INT              2147483647
# define MAX_PHILO_STR        "200"

# define COLOR_RESET          "\e[0m"
# define COLOR_RED            "\e[31m"
# define COLOR_GREEN          "\e[32m"
# define COLOR_PURPLE         "\e[35m"
# define COLOR_CYAN           "\e[36m"

# define MSG_PROG_NAME        "philo:"
# define MSG_USAGE            "%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define MSG_ERR_INPUT_DIGIT  "%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define MSG_ERR_INPUT_RANGE  "%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define MSG_ERR_THREAD       "%s Error: Could not create thread.\n"
# define MSG_ERR_MALLOC       "%s Error: Could not allocate memory.\n"
# define MSG_ERR_MUTEX        "%s Error: Could not create mutex.\n"

/* ******************** (ALIASES) ******************** */

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_lock;
typedef struct timeval	t_timeval;
typedef struct s_agent	t_agent;

/* **************************************************** */
/*                  STRUCT DEFINITIONS                  */
/* **************************************************** */

typedef struct s_table
{
	time_t			start_time;
	unsigned int	nb_agents;
	t_thread		reaper;
	time_t			tt_die;
	time_t			tt_eat;
	time_t			tt_sleep;
	int				meals_required;
	bool			sim_end;
	t_lock			end_lock;
	t_lock			print_lock;
	t_lock			*forks;
	t_agent			**agents;
}					t_table;

typedef struct s_agent
{
	t_thread		thread;
	unsigned int	meals_eaten;
	unsigned int	fork[2];
	unsigned int	id;
	t_lock			last_meal_lock;
	time_t			last_meal;
	t_table			*table;
}					t_agent;

typedef enum e_state
{
	STATE_DIED = 0,
	STATE_EAT = 1,
	STATE_SLEEP = 2,
	STATE_THINK = 3,
	STATE_FORK1 = 4,
	STATE_FORK2 = 5
}	t_state;

/*******************************************************
 *           PHILOSOPHERS PROJECT FUNCTIONS            *
 *******************************************************/

/* cleanup file functions */

void	*table_free(t_table *table);
void	mutexes_destroy(t_table *table);
int		msg_print(char *str, char *detail, int exit_no);
int		error_fail(char *str, char *detail, t_table *table);
void	*error_nullptr(char *str, char *detail, t_table *table);

/* init file functions */

t_table	*table_init(int ac, char **av, int i);

/* monitor file functions */

bool	stop_check(t_table *table);
void	*monitor(void *data);

/* parsing file functions */

int		ft_atoi(char *str);
bool	validate_arguments(int ac, char **av);

/* parsing file functions */

void	*agent_routine(void *data);

/* status file functions */

void	log_state(t_agent *agent, bool reaper_report, t_state state);
void	log_simulation_outcome(t_table *table);

/* time file functions */

time_t	time_now_ms(void);
void	agent_sleep(t_table *table, time_t duration_ms);
void	delay_start(time_t start_time);

#endif
