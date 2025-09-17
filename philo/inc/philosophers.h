/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:55 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 15:44:27 by mbah             ###   ########.fr       */
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

# define MAX_PHILO_NUM        250
# define MAX_INT              2147483647
# define MAX_PHILO_STR        "250"

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

/******************************************************
*            INITIALIZE TABLE, PHILOS AND FORKS       *
*******************************************************/

/**
 * @brief Initializes the table with philosophers and forks.
 * @param table Pointer to the table to be initialized.
 * @param philos Pointer to the array of philosophers.
 * @param forks Pointer to the array of mutexes representing the forks.
*/
void	init_table(t_table *table, t_philo *philos, t_mutex *forks);

/**
  * @brief Initializes philosophers with their respective 
  * mutexes and other properties.
  * @param table Pointer to the table structure.
  * @param philos Pointer to the array of philosophers.
  * @param forks Pointer to the array of forks.
  * @param av Array of command-line arguments.
*/
void	init_philos(t_table *table, t_philo *philos, t_mutex *forks, char **av);

/**
  * @brief Initializes forks by creating mutexes for them.
  * @param table Pointer to the table structure.
  * @param forks Pointer to the mutex array for the forks.
  * @param quantity Number of forks (equal to the number of philosophers).
*/
void	init_forks(t_table *table, t_mutex *forks, int quantity);

/******************************************************
*                  EXTERNAL FUNCTIONS                 *
*******************************************************/

/**
  * @brief Computes the length of a string.
  * @param str The string whose length is to be computed.
  * @return The length of the string.
*/
size_t	ft_strlen(const char *str);

/**
  * @brief Converts a string to an integer.
  * @param str The string to be converted.
  * @return The integer value represented by the string.
*/
int		ft_atoi(const char *str);

/**
  * @brief Gets the time elapsed since the philosopher's last meal.
  * @param philo The philosopher whose time since last meal is to be calculated.
  * @return The time in milliseconds since the philosopher's last meal.
*/
size_t	time_since_last_meal(t_philo philo);

/*******************************************************
 *                  PHILO UTILS FUNCTIONS              *
 *******************************************************/

/**
  * @brief Displays an error message and exits the program.
  * @param err_msg The error message to display.
  * @param exit_status The status code for exit.
*/
void	an_error_occured(char *err_msg, int exit_status);

/**
  * @brief Sleeps for a specified amount of time.
  * @param to_sleep The duration (in milliseconds) to sleep.
*/
void	ft_usleep(size_t to_sleep);

/**
  * @brief Gets the current time in milliseconds.
  * @return The current time in milliseconds.
*/
size_t	get_time_now(void);

/**
  * @brief Displays an action performed by a philosopher.
  * @param action_msg The action message to display.
  * @param philo The philosopher who performed the action.
*/
void	display_action(char *action_msg, t_philo *philo);

/**
  * @brief Cleans up resources after the simulation and 
  * displays an error message if necessary.
  * @param table Pointer to the table structure.
  * @param err_msg The error message to display.
  * @param nb_forks Number of forks involved.
  * @param exit_status The exit status code.
*/
void	clean_up(t_table *table, char *err_msg, int nb_forks, int exit_status);

/*******************************************************
 *              CHECK ARGUMENTS FUNCTIONS              *
 *******************************************************/

/**
  * @brief Checks if the command-line arguments are valid.
  * @param argc The number of arguments.
  * @param argv Array of argument strings.
*/
void	check_argument(int argc, const char **argv);

/*******************************************************
 *             DINING SIMULATION FUNCTIONS             *
 *******************************************************/

/**
  * @brief Runs the dining simulation with multiple threads.
  * @param table Pointer to the table structure.
*/
void	run_simulation_threads(t_table *table);

#endif
