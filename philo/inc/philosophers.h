/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:55 by mbah              #+#    #+#             */
/*   Updated: 2025/04/07 17:00:13 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX_NUMBER	200
# define MAX_OF_INT			2147483647

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
