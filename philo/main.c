/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:01:34 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/13 11:01:56 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	what_time(void)
{
	struct timeval	currtime;
	unsigned long	ms;

	gettimeofday(&currtime, NULL);
	ms = (currtime.tv_sec * 1000) + (currtime.tv_usec /  1000);
	return (ms);
}

void	eating_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->index]);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  %d has taken a fork\n", what_time(), philo->index + 1);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->fork[(philo->index + 1) % philo->data->nph]);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  %d has taken a fork\n", what_time(), philo->index + 1);
	pthread_mutex_unlock(&philo->data->print);
	philo->last_eat = what_time();
	philo->philo_eat++;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  %d is eating\n", what_time(), philo->index + 1);
	if (philo->philo_eat == philo->data->eat_nbr)
		philo->data->counter++;
	pthread_mutex_unlock(&philo->data->print);
	usleep((philo->data->eat_time - 10) * 1000);
	while (what_time() <= philo->last_eat + philo->data->sleep_time);
	pthread_mutex_unlock(&philo->data->fork[philo->index]);
	pthread_mutex_unlock(&philo->data->fork[(philo->index + 1) % philo->data->nph]);
}

void	sleeping_process(t_philo *philo)
{
	unsigned long	ms;

	ms = what_time();
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  %d is sleeping\n", ms, philo->index + 1);
	pthread_mutex_unlock(&philo->data->print);
	usleep((philo->data->sleep_time - 10) * 1000);
	while (what_time() <= ms + philo->data->sleep_time);
}

void	thinking_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  %d is thinking\n", what_time(), philo->index + 1);
	pthread_mutex_unlock(&philo->data->print);
}

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

int	fill_args(t_data *data, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		data->counter = 0;
		if (pthread_mutex_init(&data->print, NULL))
			return (-1);
		data->nph = ft_atoi(av[1]);
		if (data->nph == -1 || data->nph > 200)
			return (-1);
		data->die_time = ft_atoi(av[2]);
		if (data->die_time == -1 || data->die_time < 60)
			return (-1);
		data->eat_time = ft_atoi(av[3]);
		if (data->eat_time == -1 || data->eat_time < 60)
			return (-1);
		data->sleep_time = ft_atoi(av[4]);
		if (data->sleep_time == -1 || data->sleep_time < 60)
			return (-1);
		if (ac == 6)
			data->eat_nbr = ft_atoi(av[5]);
		else
			data->eat_nbr = 0;
		if (data->eat_nbr == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

void	fill_philo(t_philo *philo, t_data *data)
{
	unsigned long	ms;
	int				i;

	i = 0;
	ms = what_time();
	while (i < data->nph)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		philo[i].data = data;
		philo[i].index = i;
		philo[i].last_eat = ms;
		philo[i].philo_eat = 0;
		i++;
	}
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