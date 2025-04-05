/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:59:55 by mbah              #+#    #+#             */
/*   Updated: 2025/04/05 01:21:36 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/philosophers.h"
#include <stdlib.h>

static void	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		clean_up(table, "Error: Failed to init print mutex", 0, EXIT_FAILURE);
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		clean_up(table, "Error: Failed to init meal mutex", 0, EXIT_FAILURE);
}

void	init_table(t_table *table, t_philo *philos, t_mutex *forks)
{
	if (!table || !philos || !forks)
		clean_up(NULL, "Error: Null pointer in table init", 0, EXIT_FAILURE);
	table->philos = philos;
	table->forks = forks;
	init_table_mutexes(table);
}

void	init_philos(t_table *table, t_philo *philos, t_mutex *forks, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		philos[i].id = (i + 1);
		philos[i].philo_nb = ft_atoi(av[1]);
		philos[i].times.time_to_die = ft_atoi(av[2]);
		philos[i].times.time_to_eat = ft_atoi(av[3]);
		philos[i].times.time_to_sleep = ft_atoi(av[4]);
		philos[i].times.time_of_last_meal = get_time_now();
		philos[i].times.time_at_born = get_time_now();
		philos[i].meals_eat = 0;
		philos[i].mutexes.left_fork = &forks[i];
		philos[i].must_eat = -1;
		if (!i)
			philos[i].mutexes.right_fork = &forks[philos[i].philo_nb - 1];
		else
			philos[i].mutexes.right_fork = &forks[(i - 1)];
		if (av[5])
			philos[i].must_eat = ft_atoi(av[5]);
		philos[i].mutexes.print_lock = &table->print_lock;
		philos[i].mutexes.meal_lock = &table->meal_lock;
	}
}

void	init_forks(t_table *table, t_mutex *forks, int quantity)
{
	int	i;

	i = 0;
	while (i < quantity)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			clean_up(table, "Error: Mutex init", i, EXIT_FAILURE);
		i++;
	}
}
