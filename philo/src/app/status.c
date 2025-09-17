/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:35:13 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 18:42:29 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Prints the agent's state in a colorful debug format.
 *
 * This function displays a timestamped, colorized message describing
 * the agent's current state. For fork-taking states, the specific
 * fork ID is also included.
 *
 * @param agent Pointer to the agent structure.
 * @param color ANSI color escape string for formatting.
 * @param msg Message string describing the state.
 * @param state The state being reported (e.g. STATE_FORK1, STATE_EAT).
 */
static void	display_state_debug(t_agent *agent, char *color,
								char *msg, t_state state)
{
	time_t	timestamp;

	timestamp = time_now_ms() - agent->table->start_time;
	if (state == STATE_FORK1)
		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
			timestamp, color, agent->id + 1, msg, agent->fork[0]);
	else if (state == STATE_FORK2)
		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
			timestamp, color, agent->id + 1, msg, agent->fork[1]);
	else
		printf("[%10ld]\t%s%03d\t%s\e[0m\n",
			timestamp, color, agent->id + 1, msg);
}

/**
 * @brief Logs the agent's state in debug mode.
 *
 * This function redirects to `display_state_debug()` using
 * predefined colors and messages for each state.
 *
 * @param agent Pointer to the agent structure.
 * @param state Current agent state.
 */
static void	log_state_debug(t_agent *agent, t_state state)
{
	if (state == STATE_DIED)
		display_state_debug(agent, COLOR_RED, "died", state);
	else if (state == STATE_EAT)
		display_state_debug(agent, COLOR_GREEN, "is eating", state);
	else if (state == STATE_SLEEP)
		display_state_debug(agent, COLOR_CYAN, "is sleeping", state);
	else if (state == STATE_THINK)
		display_state_debug(agent, COLOR_CYAN, "is thinking", state);
	else if (state == STATE_FORK1)
		display_state_debug(agent, COLOR_PURPLE, "has taken a fork", state);
	else if (state == STATE_FORK2)
		display_state_debug(agent, COLOR_PURPLE, "has taken a fork", state);
}

/**
 * @brief Prints the agent's state in plain text.
 *
 * Required project format:
 *      [timestamp_in_ms] [agent_id] [state_message]
 *
 * @param agent Pointer to the agent structure.
 * @param msg Plain message string describing the state.
 */
static void	display_state_plain(t_agent *agent, char *msg)
{
	printf("%ld %d %s\n",
		time_now_ms() - agent->table->start_time,
		agent->id + 1, msg);
}

/**
 * @brief Logs the agent's state in the required format.
 *
 * This function prints the agent's current state as long as the
 * simulation is active. It locks the `print_lock` mutex to avoid
 * interleaved messages from multiple threads.
 *
 * If `DEBUG_FORMATTING` is enabled, it uses the debug output with
 * colors and fork IDs. Otherwise, it prints the plain required format.
 *
 * The `reaper_report` flag allows the reaper thread to log a death
 * even after the simulation stop flag has been set.
 *
 * @param agent Pointer to the agent structure.
 * @param reaper_report Whether the log comes from the reaper thread.
 * @param state Current agent state.
 */
void	log_state(t_agent *agent, bool reaper_report, t_state state)
{
	pthread_mutex_lock(&agent->table->print_lock);
	if (stop_check(agent->table) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&agent->table->print_lock);
		return ;
	}
	if (DEBUG_FORMATTING == true)
	{
		log_state_debug(agent, state);
		pthread_mutex_unlock(&agent->table->print_lock);
		return ;
	}
	if (state == STATE_DIED)
		display_state_plain(agent, "died");
	else if (state == STATE_EAT)
		display_state_plain(agent, "is eating");
	else if (state == STATE_SLEEP)
		display_state_plain(agent, "is sleeping");
	else if (state == STATE_THINK)
		display_state_plain(agent, "is thinking");
	else if (state == STATE_FORK1 || state == STATE_FORK2)
		display_state_plain(agent, "has taken a fork");
	pthread_mutex_unlock(&agent->table->print_lock);
}

/**
 * @brief Logs the outcome of the simulation.
 *
 * If `meals_required` is set to a positive value, this function
 * counts how many agents reached the required meal threshold and
 * prints the result. Used only for debugging.
 *
 * Example output:
 *      3/5 agents had at least 7 meals.
 *
 * @param table Pointer to the main simulation table structure.
 */
void	log_simulation_outcome(t_table *table)
{
	unsigned int	i;
	unsigned int	full_count;

	if (table->meals_required <= 0)
		return ;
	full_count = 0;
	i = 0;
	while (i < table->nb_agents)
	{
		if (table->agents[i]->meals_eaten
			>= (unsigned int)table->meals_required)
			full_count++;
		i++;
	}
	pthread_mutex_lock(&table->print_lock);
	printf("%d/%d agents had at least %d meals.\n",
		full_count, table->nb_agents, table->meals_required);
	pthread_mutex_unlock(&table->print_lock);
}
