/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:32:18 by sabazyan          #+#    #+#             */
/*   Updated: 2022/09/28 14:50:27 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	four_args(t_philo *ph, long long int start, long long int time)
{
	while (!forks(ph, start, time))
	{
		print_actions(ph, "is eating\n", get_time() - time, ph->num);
		start = get_time();
		while (get_time() - start != ph->ms_eat)
			;
		pthread_mutex_unlock(ph->left);
		pthread_mutex_unlock(ph->right);
		print_actions(ph, "is sleeping\n", get_time() - time, ph->num);
		start = get_time();
		while (get_time() - start != ph->ms_sleep)
			;
		print_actions(ph, "is thinking\n", get_time() - time, ph->num);
	}
}

void	five_args(t_philo *ph, long long int start, long long int time)
{
	while (ph->count && !forks(ph, start, time))
	{
		print_actions(ph, "is eating\n", get_time() - time, ph->num);
		start = get_time();
		while (get_time() - start != ph->ms_eat)
			;
		pthread_mutex_unlock(ph->left);
		pthread_mutex_unlock(ph->right);
		print_actions(ph, "is sleeping\n", get_time() - time, ph->num);
		start = get_time();
		while (get_time() - start != ph->ms_sleep)
			;
		print_actions(ph, "is thinking\n", get_time() - time, ph->num);
		ph->count--;
	}
}

int	forks(t_philo *ph, long long int start, long long int time)
{
	pthread_mutex_lock(ph->left);
	print_actions(ph, "has taken a left fork\n", get_time() - time, ph->num);
	pthread_mutex_lock(ph->right);
	print_actions(ph, "has taken a right fork\n", get_time() - time, ph->num);
	if (get_time() - start + ph->ms_eat >= ph->ms_die && *(ph->is_dead) != 1)
	{
		while (get_time() - start != ph->ms_die)
			;
		print_actions(ph, "died\n", get_time() - time, ph->num);
		*(ph->is_dead) = 1;
		return (1);
	}
	return (0);
}

void	init_mutex(char **args, pthread_mutex_t *mutex, t_philo *philo,
		pthread_mutex_t	print)
{
	int	i;

	i = 0;
	while (i < ft_atoi(args[1]))
	{
		philo[i].print = &print;
		philo[i].is_dead = philo[0].is_dead;
		i++;
	}
	i = 0;
	while (i < ft_atoi(args[1]))
	{
		pthread_mutex_init(&mutex[i], NULL);
		philo[i].num = i + 1;
		philo[i].ms_die = ft_atoi(args[2]);
		philo[i].ms_eat = ft_atoi(args[3]);
		philo[i].ms_sleep = ft_atoi(args[4]);
		if (!args[5])
			philo[i].count = -1;
		else
			philo[i].count = ft_atoi(args[5]);
		i++;
	}
}
