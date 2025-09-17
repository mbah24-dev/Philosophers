/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:55:43 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 16:17:54 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Frees all memory allocated for the simulation.
 *
 * Iterates through the table structure, releasing fork locks,
 * philosopher instances, and the table itself.
 *
 * @param table Pointer to the simulation table.
 * @return Always returns NULL for convenience.
 */
void	*table_free(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->forks != NULL)
		free(table->forks);
	if (table->agents != NULL)
	{
		i = 0;
		while (i < table->nb_agents)
		{
			if (table->agents[i] != NULL)
				free(table->agents[i]);
			i++;
		}
		free(table->agents);
	}
	free(table);
	return (NULL);
}

/**
 * @brief Destroys all mutexes created during the simulation.
 *
 * Includes fork locks, agent meal-time locks, and global locks
 * for printing and simulation end control.
 *
 * @param table Pointer to the simulation table.
 */
void	mutexes_destroy(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_agents)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->agents[i]->last_meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->end_lock);
}

/**
 * @brief Prints an error or status message.
 *
 * Formats and prints the given message with the program name.
 *
 * @param str Format string (message template).
 * @param detail Optional detail string to include (can be NULL).
 * @param exit_no Exit code to return.
 * @return The provided exit_no.
 */
int	msg_print(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, MSG_PROG_NAME);
	else
		printf(str, MSG_PROG_NAME, detail);
	return (exit_no);
}

/**
 * @brief Handles initialization failure with memory cleanup.
 *
 * Frees any allocated memory, prints an error message,
 * and returns 0 to indicate failure.
 *
 * @param str Error message format.
 * @param detail Additional error details (can be NULL).
 * @param table Pointer to the simulation table.
 * @return Always returns 0 (failure).
 */
int	error_fail(char *str, char *detail, t_table *table)
{
	if (table != NULL)
		table_free(table);
	return (msg_print(str, detail, 0));
}

/**
 * @brief Handles initialization failure returning NULL.
 *
 * Frees any allocated memory, prints an error message,
 * and returns a NULL pointer.
 *
 * @param str Error message format.
 * @param detail Additional error details (can be NULL).
 * @param table Pointer to the simulation table.
 * @return Always returns NULL.
 */
void	*error_nullptr(char *str, char *detail, t_table *table)
{
	if (table != NULL)
		table_free(table);
	msg_print(str, detail, EXIT_FAILURE);
	return (NULL);
}
