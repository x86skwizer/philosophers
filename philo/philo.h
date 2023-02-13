/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 02:31:44 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/13 10:58:34 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "./utils/utils.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct	s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				nph;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_nbr;
	int				counter;
}	t_data;

typedef struct	s_philo
{
	struct s_data	*data;
	pthread_t		id;
	int				index;
	unsigned long	last_eat;
	int				philo_eat;

}	t_philo;

#endif