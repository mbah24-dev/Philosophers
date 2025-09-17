/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:50:23 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 18:23:29 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Handles the eating and sleeping routine of an agent.
 *
 * The agent will pick up the two forks (mutex locks) in order, eat for
 * the specified time, record the time of the last meal, and then sleep
 * for the configured time. The number of meals eaten is updated.
 *
 * @param agent Pointer to the agent structure.
 */
static void	perform_eat_sleep(t_agent *agent)
{
	pthread_mutex_lock(&agent->table->forks[agent->fork[0]]);
	log_state(agent, false, STATE_FORK1);
	pthread_mutex_lock(&agent->table->forks[agent->fork[1]]);
	log_state(agent, false, STATE_FORK2);
	log_state(agent, false, STATE_EAT);
	pthread_mutex_lock(&agent->last_meal_lock);
	agent->last_meal = time_now_ms();
	pthread_mutex_unlock(&agent->last_meal_lock);
	agent_sleep(agent->table, agent->table->tt_eat);
	if (!stop_check(agent->table))
	{
		pthread_mutex_lock(&agent->last_meal_lock);
		agent->meals_eaten++;
		pthread_mutex_unlock(&agent->last_meal_lock);
	}
	log_state(agent, false, STATE_SLEEP);
	pthread_mutex_unlock(&agent->table->forks[agent->fork[1]]);
	pthread_mutex_unlock(&agent->table->forks[agent->fork[0]]);
	agent_sleep(agent->table, agent->table->tt_sleep);
}

/**
 * @brief Handles the thinking routine of an agent.
 *
 * The time to think is calculated based on how much time has passed
 * since the last meal, the eating duration, and the time to die.
 * This helps stagger eating and reduce fork conflicts.
 *
 * @param agent Pointer to the agent structure.
 * @param silent If true, suppresses printing of thinking status.
 */
static void	perform_think(t_agent *agent, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&agent->last_meal_lock);
	time_to_think = (agent->table->tt_die
			- (time_now_ms() - agent->last_meal)
			- agent->table->tt_eat) / 2;
	pthread_mutex_unlock(&agent->last_meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		log_state(agent, false, STATE_THINK);
	agent_sleep(agent->table, time_to_think);
}

/**
 * @brief Routine for a single agent (only one fork available).
 *
 * The agent picks up the single fork, waits for the time to die,
 * and then dies. This avoids deadlocks in the single-agent scenario.
 *
 * @param agent Pointer to the agent structure.
 * @return NULL Always returns NULL for thread routine.
 */
static void	*single_agent_routine(t_agent *agent)
{
	pthread_mutex_lock(&agent->table->forks[agent->fork[0]]);
	log_state(agent, false, STATE_FORK1);
	agent_sleep(agent->table, agent->table->tt_die);
	log_state(agent, false, STATE_DIED);
	pthread_mutex_unlock(&agent->table->forks[agent->fork[0]]);
	return (NULL);
}

/**
 * @brief Main routine for an agent thread.
 *
 * Agents alternate between eating, sleeping, and thinking. Even-ID agents
 * start by thinking to reduce fork conflicts with odd-ID agents.
 *
 * @param data Pointer to the agent structure.
 * @return NULL Always returns NULL for thread routine.
 */
void	*agent_routine(void *data)
{
	t_agent	*agent;

	agent = (t_agent *)data;
	if (agent->table->meals_required == 0)
		return (NULL);
	pthread_mutex_lock(&agent->last_meal_lock);
	agent->last_meal = agent->table->start_time;
	pthread_mutex_unlock(&agent->last_meal_lock);
	delay_start(agent->table->start_time);
	if (agent->table->tt_die == 0)
		return (NULL);
	if (agent->table->nb_agents == 1)
		return (single_agent_routine(agent));
	else if (agent->id % 2)
		perform_think(agent, true);
	while (!stop_check(agent->table))
	{
		perform_eat_sleep(agent);
		perform_think(agent, false);
	}
	return (NULL);
}
