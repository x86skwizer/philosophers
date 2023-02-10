/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 02:31:44 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/10 17:40:02 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "./utils/utils.h"
#include <pthread.h>
#include <unistd.h>

typedef struct	s_data
{
	pthread_mutex_t	*fork;
	int				nph;
	t_philo			*philo;
}	t_data;

typedef struct	s_philo
{
	pthread_t		th;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				index;
}	t_philo;

#endif