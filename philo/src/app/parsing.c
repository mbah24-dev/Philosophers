/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:42:35 by mbah              #+#    #+#             */
/*   Updated: 2025/09/17 18:23:26 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Check if a string contains only numeric digits (0-9).
 *
 * Iterates through the input string and validates that each
 * character is a digit. If any non-digit character is found,
 * the function returns false.
 *
 * @param str Input string to check.
 * @return true if the string contains only digits, false otherwise.
 */
static bool	is_numeric_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Convert a numeric string into an integer.
 *
 * Converts a digit-only string into an integer within the valid
 * range [0, INT_MAX]. If the converted number exceeds INT_MAX,
 * the function returns -1 as an error flag.
 *
 * @param str Input string containing only digits.
 * @return int The converted integer, or -1 if out of range.
 */
int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

/**
 * @brief Validate command-line arguments for the simulation.
 *
 * Ensures all required arguments are valid numbers within their
 * expected ranges. Specifically:
 * - All arguments must contain only digits.
 * - The number of agents (philosophers) must be between 1 and MAX_AGENTS.
 * - Time and meal arguments must be within the integer range.
 *
 * Prints an error message and returns false if validation fails.
 *
 * @param ac Argument count.
 * @param av Argument values (as strings).
 * @return true if all arguments are valid, false otherwise.
 */
bool	validate_arguments(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!is_numeric_string(av[i]))
			return (msg_print(MSG_ERR_INPUT_DIGIT, av[i], false));
		nb = ft_atoi(av[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILO_NUM))
			return (msg_print(MSG_ERR_INPUT_RANGE, MAX_PHILO_STR, false));
		if (i != 1 && nb == -1)
			return (msg_print(MSG_ERR_INPUT_DIGIT, av[i], false));
		i++;
	}
	return (true);
}
