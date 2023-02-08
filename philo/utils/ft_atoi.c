/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:53:01 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/01 02:26:10 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	initiate_atoi(char **src, int *sign)
{
	while (ft_strchr(" \n\f\r\t\v", **src))
		(*src)++;
	*sign = 1;
	if (**src == '-')
	{
		*sign = -1;
		(*src)++;
	}
	else if (**src == '+')
		(*src)++;
}

int	ft_atoi(const char *str)
{
	char		*src;
	long long	num;
	int			sign;

	if (!ft_strlen(str))
		return (0);
	src = (char *) str;
	num = 0;
	initiate_atoi (&src, &sign);
	while (*src >= '0' && *src <= '9')
	{
		if (num * 10 + (*src - 48) >= num)
			num = num * 10 + (*src - 48);
		else
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		src++;
	}
	// if ((num * sign) > 2147483647 || (num * sign) < -2147483648)
	// 	ft_exit();
	return (num * sign);
}
