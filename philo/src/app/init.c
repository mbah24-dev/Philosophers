/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:11:34 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 16:44:04 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Allocate and initialize fork mutexes.
 *
 * @param table Pointer to the simulation table.
 * @return Pointer to the array of fork mutexes, or NULL on failure.
 */
static t_lock	*forks_init(t_table *table)
{
	t_lock			*forks;
	unsigned int	i;

	forks = malloc(sizeof(t_lock) * table->nb_agents);
	if (!forks)
		return (error_nullptr(MSG_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->nb_agents)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_nullptr(MSG_ERR_MUTEX, NULL, 0));
		i++;
	}
	return (forks);
}

/**
 * @brief Assign fork IDs to an agent.
 *
 * Odd/even IDs have different fork orders to prevent deadlocks.
 *
 * @param agent Pointer to the agent (philosopher).
 */
static void	forks_assign(t_agent *agent)
{
	agent->fork[0] = agent->id;
	agent->fork[1] = (agent->id + 1) % agent->table->nb_agents;
	if (agent->id % 2)
	{
		agent->fork[0] = (agent->id + 1) % agent->table->nb_agents;
		agent->fork[1] = agent->id;
	}
}

/**
 * @brief Allocate and initialize agents (philosophers).
 *
 * @param table Pointer to the simulation table.
 * @return Pointer to the array of agent pointers, or NULL on failure.
 */
static t_agent	**agents_init(t_table *table)
{
	t_agent			**agents;
	unsigned int	i;

	agents = malloc(sizeof(t_agent) * table->nb_agents);
	if (!agents)
		return (error_nullptr(MSG_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->nb_agents)
	{
		agents[i] = malloc(sizeof(t_agent));
		if (!agents[i])
			return (error_nullptr(MSG_ERR_MALLOC, NULL, 0));
		if (pthread_mutex_init(&agents[i]->last_meal_lock, 0) != 0)
			return (error_nullptr(MSG_ERR_MUTEX, NULL, 0));
		agents[i]->table = table;
		agents[i]->id = i;
		agents[i]->meals_eaten = 0;
		forks_assign(agents[i]);
		i++;
	}
	return (agents);
}

/**
 * @brief Initialize global mutexes (forks, print, simulation end).
 *
 * @param table Pointer to the simulation table.
 * @return true if successful, false otherwise.
 */
static bool	mutexes_init(t_table *table)
{
	table->forks = forks_init(table);
	if (!table->forks)
		return (false);
	if (pthread_mutex_init(&table->end_lock, 0) != 0)
		return (error_fail(MSG_ERR_MUTEX, NULL, table));
	if (pthread_mutex_init(&table->print_lock, 0) != 0)
		return (error_fail(MSG_ERR_MUTEX, NULL, table));
	return (true);
}

/**
 * @brief Initialize the simulation table.
 *
 * Allocates memory for the table, sets simulation parameters,
 * and initializes agents and mutexes.
 *
 * @param ac Argument count.
 * @param av Argument values.
 * @param i Index where table parameters start.
 * @return Pointer to the initialized table, or NULL on failure.
 */
t_table	*table_init(int ac, char **av, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (error_nullptr(MSG_ERR_MALLOC, NULL, 0));
	table->nb_agents = integer_atoi(av[i++]);
	table->tt_die = integer_atoi(av[i++]);
	table->tt_eat = integer_atoi(av[i++]);
	table->tt_sleep = integer_atoi(av[i++]);
	table->meals_required = -1;
	if (ac - 1 == 5)
		table->meals_required = ft_atoi(av[i]);
	table->agents = agents_init(table);
	if (!table->agents)
		return (NULL);
	if (!mutexes_init(table))
		return (NULL);
	table->sim_end = false;
	return (table);
}
