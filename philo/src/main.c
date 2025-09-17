/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:15 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 18:40:47 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Launch the simulation by creating agent threads and the reaper thread.
 *
 * Initializes the start time, creates a thread for each agent, and starts
 * the grim reaper thread if there is more than one agent.
 *
 * @param table Pointer to the simulation table.
 * @return true if the simulation started successfully, false on error.
 */
static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = time_now_ms() + (table->nb_agents * 2 * 10);
	i = 0;
	while (i < table->nb_agents)
	{
		if (pthread_create(&table->agents[i]->thread, NULL,
				&agent_routine, table->agents[i]) != 0)
			return (error_fail(MSG_ERR_THREAD, NULL, table));
		i++;
	}
	if (table->nb_agents > 1)
	{
		if (pthread_create(&table->reaper, NULL,
				&monitor, table) != 0)
			return (error_fail(MSG_ERR_THREAD, NULL, table));
	}
	return (true);
}

/**
 * @brief Stop the simulation by joining threads and cleaning resources.
 *
 * Joins all agent threads and the reaper thread, prints outcome 
 * if debug is enabled,
 * destroys mutexes, and frees allocated memory.
 *
 * @param table Pointer to the simulation table.
 */
static void	stop_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_agents)
	{
		pthread_join(table->agents[i]->thread, NULL);
		i++;
	}
	if (table->nb_agents > 1)
		pthread_join(table->reaper, NULL);
	if (DEBUG_FORMATTING == true && table->meals_required != -1)
		log_simulation_outcome(table);
	mutexes_destroy(table);
	table_free(table);
}

/**
 * @brief Entry point of the program.
 *
 * Validates input arguments, initializes the simulation table, starts
 * the simulation, and stops it when finished.
 *
 * @param ac Argument count.
 * @param av Argument vector.
 * @return Exit status.
 */
int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (msg_print(MSG_USAGE, NULL, EXIT_FAILURE));
	if (!validate_arguments(ac, av))
		return (EXIT_FAILURE);
	table = table_init(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	stop_simulation(table);
	return (EXIT_SUCCESS);
}
