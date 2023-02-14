/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 02:31:44 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/14 07:00:53 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./utils/utils.h"
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data
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

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		id;
	int				index;
	unsigned long	last_eat;
	int				philo_eat;

}	t_philo;

unsigned long	what_time(void);
int				check_arg_num(int ac);
int				fill_args(t_data *data, int ac, char **av);
void			fill_philo(t_philo *philo, t_data *data);
void			eating_process(t_philo *philo);
void			sleeping_process(t_philo *philo);
void			thinking_process(t_philo *philo);

#endif