/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:04:22 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 18:41:34 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Sets the simulation stop flag.
 *
 * Only the monitor (grim reaper) thread should set this flag.
 * When true, the simulation has reached an end condition.
 *
 * @param table Pointer to the simulation table.
 * @param state Boolean state (true to stop, false to continue).
 */
static void	stop_set(t_table *table, bool state)
{
	pthread_mutex_lock(&table->end_lock);
	table->sim_end = state;
	pthread_mutex_unlock(&table->end_lock);
}

/**
 * @brief Checks if the simulation should stop.
 *
 * Uses a mutex to safely read the stop flag,
 * accessible from any thread.
 *
 * @param table Pointer to the simulation table.
 * @return true if the stop flag is set, false otherwise.
 */
bool	stop_check(t_table *table)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&table->end_lock);
	if (table->sim_end == true)
		ret = true;
	pthread_mutex_unlock(&table->end_lock);
	return (ret);
}

/**
 * @brief Determines if a philosopher has died.
 *
 * Compares current time with the philosopher's last meal.
 * If the time exceeds `time_to_die`, sets the stop flag
 * and prints the death status.
 *
 * @param agent Pointer to the philosopher.
 * @return true if the philosopher has died, false otherwise.
 */
static bool	agent_dead(t_agent *agent)
{
	time_t	now;

	now = time_now_ms();
	if ((now - agent->last_meal) >= agent->table->tt_die)
	{
		stop_set(agent->table, true);
		log_state(agent, true, STATE_DIED);
		pthread_mutex_unlock(&agent->last_meal_lock);
		return (true);
	}
	return (false);
}

/**
 * @brief Checks if an end condition is reached.
 *
 * Iterates over all philosophers to verify:
 *  - If one has died.
 *  - If all have eaten enough times.
 *
 * @param table Pointer to the simulation table.
 * @return true if an end condition is reached, false otherwise.
 */
static bool	end_reached(t_table *table)
{
	unsigned int	i;
	bool			all_fed;

	all_fed = true;
	i = 0;
	while (i < table->nb_agents)
	{
		pthread_mutex_lock(&table->agents[i]->last_meal_lock);
		if (agent_dead(table->agents[i]))
			return (true);
		if (table->meals_required != -1)
			if (table->agents[i]->meals_eaten < \
				(unsigned int)table->meals_required)
				all_fed = false;
		pthread_mutex_unlock(&table->agents[i]->last_meal_lock);
		i++;
	}
	if (table->meals_required != -1 && all_fed == true)
	{
		stop_set(table, true);
		return (true);
	}
	return (false);
}

/**
 * @brief Monitor thread routine (grim reaper).
 *
 * Continuously checks for philosopher deaths or
 * completion of the required number of meals.
 *
 * @param data Pointer to the simulation table.
 * @return Always NULL.
 */
void	*monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->meals_required == 0)
		return (NULL);
	stop_set(table, false);
	delay_start(table->start_time);
	while (true)
	{
		if (end_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
