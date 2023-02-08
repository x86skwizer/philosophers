/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 02:31:44 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/04 13:32:27 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "./utils/utils.h"
#include <pthread.h>
#include <unistd.h>

typedef struct	s_philo
{
	pthread_t		*th;
	pthread_mutex_t	*fork;
	int				nph;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				index;
}	t_philo;


#endif