/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:15 by mbah              #+#    #+#             */
/*   Updated: 2025/04/03 22:56:49 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	*func1(void *arg)
{
	int *n = (int *)arg;
	(*n)++;
	pthread_exit(NULL);
}

static void	*func2(void *arg)
{
	int *n = (int *)arg;
	(*n)--;
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	pthread_t	t1;
	pthread_t	t2;
	int			n = 100;
	int 		i = 0;
	struct timeval current_time;
	pthread_mutex_t mutex;
	
	while (i++ < 100)
	{
		pthread_create(&t1, NULL, func1, &n);
		pthread_create(&t2, NULL, func2, &n);
		printf("n = %i\n", n);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_init(&mutex, NULL);
 	gettimeofday(&current_time, NULL);
  	printf("seconds : %ld\nmicro seconds : %d",
    	current_time.tv_sec, current_time.tv_usec);
	return (0);
}
