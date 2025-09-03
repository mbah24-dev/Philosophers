/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:36:30 by mbah              #+#    #+#             */
/*   Updated: 2025/08/30 16:01:28 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void	an_error_occured(char *err_msg, int exit_status)
{
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg) + 1);
	exit(exit_status);
}

size_t	get_time_now(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		an_error_occured("Error: get time of day", EXIT_FAILURE);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t to_sleep)
{
	size_t	begin;

	begin = get_time_now();
	while ((get_time_now() - begin < to_sleep))
		usleep(500);
}

void	display_action(char *action_msg, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->mutexes.print_lock);
	time = get_time_now() - philo->times.time_at_born;
	printf("%ld %d %s\n", time, philo->id, action_msg);
	pthread_mutex_unlock(philo->mutexes.print_lock);
}

void	clean_up(t_table *table, char *err_msg, int nb_forks, int exit_status)
{
	int	i;

	i = 0;
	while (i < nb_forks)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->print_lock);
	an_error_occured(err_msg, exit_status);
}
