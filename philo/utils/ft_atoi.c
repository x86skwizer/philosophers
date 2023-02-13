/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:53:01 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/11 23:54:45 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi(char *str)
{
	long long	num;
	int			i;

	if (!ft_strlen(str))
		return (-1);
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] <= 48 || str[i] >= 57)
		return (-1);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		if (num * 10 + (str[i] - 48) >= num)
			num = num * 10 + (str[i] - 48);
		else
			return (-1);
		i++;
	}
	if (num > 2147483647)
		return (-1);
	return (num);
}
