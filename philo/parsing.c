/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 05:14:55 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/14 06:59:02 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	what_time(void)
{
	struct timeval	currtime;
	unsigned long	ms;

	gettimeofday(&currtime, NULL);
	ms = (currtime.tv_sec * 1000) + (currtime.tv_usec / 1000);
	return (ms);
}

int	check_arg_num(int ac)
{
	if (ac != 5 && ac != 6)
		return (-1);
	else
		return (0);
}

int	fill_args(t_data *data, int ac, char **av)
{
	data->counter = 0;
	pthread_mutex_init(&data->print, NULL);
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
