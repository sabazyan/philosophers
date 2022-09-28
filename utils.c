/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:09:57 by sabazyan          #+#    #+#             */
/*   Updated: 2022/09/19 18:31:00 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (sign * num);
}

long long int	get_time(void)
{
	struct timeval	current_time;
	long long int	start;

	gettimeofday(&current_time, NULL);
	start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000 ;
	return (start);
}

int	ft_isdigit(char **s)
{
	int	i;
	int	j;

	i = 1;
	while (s && s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
