/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:15 by mbah              #+#    #+#             */
/*   Updated: 2025/04/07 15:49:21 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_mutex	forks[PHILO_MAX_NUMBER];
	t_philo	philos[PHILO_MAX_NUMBER];
	t_table	table;
	int		nb_forks;

	check_argument(argc, (const char **) argv);
	nb_forks = ft_atoi(argv[1]);
	init_table(&table, philos, forks);
	init_forks(&table, forks, nb_forks);
	init_philos(&table, philos, forks, argv);
	run_simulation_threads(&table);
	clean_up(&table, NULL, nb_forks, EXIT_SUCCESS);
	return (0);
}
