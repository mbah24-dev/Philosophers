/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:08:05 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 18:23:34 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Get the current timestamp in milliseconds since the Epoch.
 *
 * Uses gettimeofday to calculate the current time in milliseconds.
 *
 * @return Current time in milliseconds.
 */
time_t	time_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Sleep for a given amount of time in milliseconds.
 *
 * During sleep, periodically checks if the simulation has ended
 * and interrupts sleep early if necessary.
 *
 * @param table Pointer to the simulation table.
 * @param duration_ms Duration of sleep in milliseconds.
 */
void	agent_sleep(t_table *table, time_t duration_ms)
{
	time_t	wake_up_time;

	wake_up_time = time_now_ms() + duration_ms;
	while (time_now_ms() < wake_up_time)
	{
		if (stop_check(table))
			break ;
		usleep(100);
	}
}

/**
 * @brief Small delay at the start of threads to synchronize execution.
 *
 * Ensures that all agent threads and the reaper thread start
 * at the same reference time.
 *
 * @param start_time Reference start time in milliseconds.
 */
void	delay_start(time_t start_time)
{
	while (time_now_ms() < start_time)
		continue ;
}
