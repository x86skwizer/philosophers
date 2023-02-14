/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:01:34 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/14 05:19:04 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (1)
	{
		eating_process(philo);
		sleeping_process(philo);
		thinking_process(philo);
	}
	return (NULL);
}

int	philo_creation(t_philo *philo, int i)
{
	int	index;

	index = 0 + i;
	while (index < philo->data->nph)
	{
		if (pthread_create(&philo[index].id, NULL, &routine, &philo[index]))
			return (-1);
		index += 2;
	}
	return (0);
}

int	bring_tolife(t_philo *philo, t_data *data)
{
	if (philo_creation(philo, 0) == -1)
	{
		pthread_mutex_lock(&data->print);
		printf("ERROR: Occured while creating threads");
		return (-1);
	}
	usleep(350);
	if (philo_creation(philo, 1) == -1)
	{
		pthread_mutex_lock(&data->print);
		printf("ERROR: Occured while creating threads");
		return (-1);
	}
	return (0);
}

int	parent(t_philo *philo)
{
	unsigned long	ms;
	unsigned long	tmp;
	int				i;

	i = 0;
	ms = what_time();
	while (i < philo->data->nph)
	{
		tmp = philo[i].last_eat + philo[i].data->die_time;
		if (ms >= tmp)
		{
				pthread_mutex_lock(&philo[i].data->print);
				printf("%ld  %d died\n", ms, philo->index + 1);
				return (0);
		}
		else if (philo[i].data->eat_nbr && philo[i].data->counter == philo[i].data->nph)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (fill_args(data, ac, av) == -1)
	{
		printf("ERROR: Wrong arguments filling");
		free(data);
		return (-1);
	}
	philo = malloc(sizeof(t_philo) * data->nph);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nph);
	fill_philo(philo, data);
	if (bring_tolife(philo, data) == -1)
		return (-1);
	while (parent(philo));
	free(data->fork);
	free(data);
	free(philo);
	return (0);
}