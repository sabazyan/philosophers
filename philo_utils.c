/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:41:19 by sabazyan          #+#    #+#             */
/*   Updated: 2022/09/28 12:16:13 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_actions(t_philo *philo, char *message,
		long long int time, int num)
{
	pthread_mutex_lock(philo->print);
	if (*(philo->is_dead) != 1)
		printf("%lld %d %s", time, num, message);
	pthread_mutex_unlock(philo->print);
}

void	one_philo(t_philo *ph)
{
	long long int	start;

	start = get_time();
	print_actions(ph, "has taken a left fork\n", get_time() - start, ph->num);
	while (get_time() - start != ph->ms_die)
		;
	print_actions(ph, "died\n", get_time() - start, ph->num);
	*(ph->is_dead) = 1;
}

void	destroy(pthread_t *th, t_philo *philo, pthread_mutex_t	*mutex)
{
	free(philo);
	free(th);
	free(mutex);
}

int	cheking_is_dead(t_philo *philo, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (*(philo[i].is_dead) == 1 || philo[i].count == 0)
		{
			pthread_mutex_lock(philo[i].print);
			return (i);
		}
		i++;
	}	
	return (-1);
}
