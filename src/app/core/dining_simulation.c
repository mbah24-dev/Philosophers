/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:10:21 by mbah              #+#    #+#             */
/*   Updated: 2025/04/07 17:25:40 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/philosophers.h"
#include <stdbool.h>
#include <stdlib.h>

static int	has_all_philos_eaten(t_philo *philos)
{
	int	nb_philo;
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (philos[0].must_eat < 0)
		return (0);
	nb_philo = philos[0].philo_nb;
	while (i < nb_philo)
	{
		pthread_mutex_lock(philos->mutexes.meal_lock);
		if (philos[i].meals_eat >= philos[i].must_eat)
			count++;
		pthread_mutex_unlock(philos->mutexes.meal_lock);
		i++;
	}
	if (count == nb_philo)
	{
		pthread_mutex_lock(philos->mutexes.print_lock);
		return (1);
	}
	return (0);
}

static void	*supervise_dining(void *param)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *) param;
	while (1)
	{
		i = 0;
		while (i < philos[0].philo_nb)
		{
			pthread_mutex_lock(philos->mutexes.meal_lock);
			if (time_since_last_meal(philos[i]) > philos[i].times.time_to_die)
			{
				pthread_mutex_unlock(philos->mutexes.meal_lock);
				display_action(" died", philos);
				pthread_mutex_lock(philos->mutexes.print_lock);
				return (NULL);
			}
			pthread_mutex_unlock(philos->mutexes.meal_lock);
			i++;
		}
		if (has_all_philos_eaten(philos))
			return (NULL);
	}
	return (NULL);
}

static void	run_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes.left_fork);
	display_action(" has taken a fork", philo);
	pthread_mutex_lock(philo->mutexes.right_fork);
	display_action(" has taken a fork", philo);
	pthread_mutex_lock(philo->mutexes.meal_lock);
	display_action(" is eating", philo);
	philo->times.time_of_last_meal = get_time_now();
	philo->meals_eat++;
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	ft_usleep(philo->times.time_to_eat);
	pthread_mutex_unlock(philo->mutexes.left_fork);
	pthread_mutex_unlock(philo->mutexes.right_fork);
	display_action(" is sleeping", philo);
	ft_usleep(philo->times.time_to_sleep);
	display_action(" is thinking", philo);
}

static void	*simulate_philosopher(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->id % 2 == 0)
		ft_usleep(2);
	pthread_mutex_lock(philo->mutexes.meal_lock);
	philo->times.time_at_born = get_time_now();
	philo->times.time_of_last_meal = get_time_now();
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	while (1)
		run_routine(philo);
	return (NULL);
}

void	run_simulation_threads(t_table *table)
{
	int			nb_philos;
	t_thread	superviser;
	int			i;

	nb_philos = table->philos[0].philo_nb;
	i = 0;
	if (pthread_create(&superviser, NULL, supervise_dining, table->philos) != 0)
		clean_up(table, "Error: can\'t create the superviser", nb_philos, 1);
	while (i < nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				simulate_philosopher, &table->philos[i]) != 0)
			clean_up(table, "Error: can\'t create this thread", nb_philos, 1);
		i++;
	}
	i = 0;
	if (pthread_join(superviser, NULL) != 0)
		clean_up(table, "Error: can\'t join de superviser", nb_philos, 1);
	while (i < nb_philos)
	{
		if (pthread_detach(table->philos[i].thread) != 0)
			clean_up(table, "Error: can\'t detach this thread", nb_philos, 1);
		i++;
	}
}
