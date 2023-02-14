/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 05:19:33 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/14 05:20:49 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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