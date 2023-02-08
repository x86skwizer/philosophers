/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:01:34 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/04 13:40:23 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 != 0)
		usleep(350);
	pthread_mutex_lock(&philo->fork[philo->index]);
	printf("%d has taken a fork 1\n", philo->index + 1);
	pthread_mutex_lock(&philo->fork[(philo->index + 1) % philo->nph]);
	printf("%d has taken a fork 2\n", philo->index +  1);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->fork[(philo->index + 1) % philo->nph]);
	free(arg);
}

int	main(int ac, char **av)
{ 
	t_philo	philo;
	t_philo	*tmp;

	if (ac == 6 || ac == 7)
	{
		philo.nph = ft_atoi(av[1]);
		philo.die_time = ft_atoi(av[2]);
		philo.eat_time = ft_atoi(av[3]);
		philo.sleep_time = ft_atoi(av[4]);
		philo.th = malloc(sizeof(pthread_t) * philo.nph);
		philo.fork = malloc(sizeof(pthread_t) * philo.nph);
		philo.index = 0;
		while (philo.index < philo.nph)
			pthread_mutex_init(&philo.fork[philo.index++], NULL);
		philo.index = 0;
		while (philo.index < philo.nph)
		{
			tmp = malloc(sizeof(t_philo));
			*tmp = philo;
			if (pthread_create(&philo.th[philo.index], NULL, &routine, (void *)tmp))
				return (-1);
			philo.index++;
		}
		philo.index = 0;
		while (philo.index < philo.nph)
		{
			if (pthread_join(philo.th[philo.index], NULL))
				return (-1);
			printf("end %d\n", philo.index);
			philo.index++;
		}
		philo.index = 0;
		while (philo.index < philo.nph)
			pthread_mutex_destroy(&philo.fork[philo.index++]);
	}
	return (0);	
}