/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:01:34 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/10 19:47:14 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

// void *routine(void *arg)
// {
// 	t_data	*data;

// 	data = (t_data *)arg;
// 	if (data->index % 2 != 0)
// 		usleep(350);
// 	pthread_mutex_lock(&data->fork[data->index]);
// 	printf("%d has taken a fork 1\n", data->index + 1);
// 	pthread_mutex_lock(&data->fork[(data->index + 1) % data->nph]);
// 	printf("%d has taken a fork 2\n", data->index +  1);
// 	pthread_mutex_unlock(&data->fork);
// 	pthread_mutex_unlock(&data->fork[(data->index + 1) % data->nph]);
// 	free(arg);
// }

void *routine(void *arg)
{
}

int	main(int ac, char **av)
{ 
	t_data	data;
	t_data	*tmp;
	int		index;

	if (ac == 6 || ac == 7)
	{
		data.nph = ft_atoi(av[1]);
		data.philo = malloc(sizeof(t_philo) * data.nph);
		index = 0;
		while (index < data.nph)
		{
			data.philo[index].die_time = ft_atoi(av[2]);
			data.philo[index].eat_time = ft_atoi(av[3]);
			data.philo[index].sleep_time = ft_atoi(av[4]);
			pthread_mutex_init(&data.philo[index].fork, NULL);
			data.philo[index].index = index;
			index++;
		}
		index = 0;
		while (index < data.nph)
		{
			if (pthread_create(&data.philo[index].th, NULL, &routine, (void *)&data))
				return (-1);
		}
		
		// while (data.philo->index < data.nph)
		// {
		// 	tmp = malloc(sizeof(t_data));
		// 	*tmp = data;
		// 	if (pthread_create(&data.th[data.philo->index], NULL, &routine, (void *)tmp))
		// 		return (-1);
		// }
		// data.index = 0;
		// while (data.index < data.nph)
		// {
		// 	if (pthread_join(data.th[data.index], NULL))
		// 		return (-1);
		// 	printf("end %d\n", data.index);
		// 	data.index++;
		// }
		// data.index = 0;
		// while (data.index < data.nph)
		// 	pthread_mutex_destroy(&data.fork[data.index++]);
	}
	return (0);	
}