/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:07:07 by mbah              #+#    #+#             */
/*   Updated: 2025/04/07 16:50:43 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/philosophers.h"
#include <stdlib.h>

static int	is_positive_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	validate_argument(const char *arg, int index)
{
	int	value;

	if (!is_positive_number(arg))
		an_error_occured("ERROR: argument is non-numeric or negative value\n",
			EXIT_FAILURE);
	value = ft_atoi(arg);
	if ((index == 1 && (value < 1 || value > PHILO_MAX_NUMBER)) || \
		(index == 5 && (value < 0 || value > MAX_OF_INT)) || \
		(index != 1 && index != 5 && (value < 1 || value > MAX_OF_INT)))
		an_error_occured("Error: Argument value out of range\n", EXIT_FAILURE);
}

void	check_argument(int argc, const char **argv)
{
	int	i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		while (++i < argc)
			validate_argument(argv[i], i);
	}
	else
		an_error_occured("Error: Expected 4 or 5 arguments\n", EXIT_FAILURE);
}
