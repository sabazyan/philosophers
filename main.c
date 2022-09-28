/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:06:51 by sabazyan          #+#    #+#             */
/*   Updated: 2022/09/28 11:25:00 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lock_fork(void *philo)
{
	t_philo			ph;
	long long int	start;
	long long int	time;

	ph = *(t_philo *)philo;
	start = get_time();
	time = get_time();
	if (ph.num % 2 == 0)
	{
		while (get_time() - start != ph.ms_eat)
			;
	}
	if (ph.count == -1)
		four_args(philo, start, time);
	else
		five_args(philo, start, time);
	return (NULL);
}

int	create_philo(char **args, int dead_id)
{
	pthread_t		*th;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print;

	th = malloc(sizeof(pthread_t) * ft_atoi(args[1]));
	mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(args[1]));
	philo = malloc(sizeof(t_philo) * ft_atoi(args[1]));
	philo[0].is_dead = malloc(sizeof(int));
	if (!th || !mutex || !philo)
	{
		destroy(th, philo, mutex);
		return (-2);
	}
	*(philo[0].is_dead) = 0;
	pthread_mutex_init(&print, NULL);
	init_mutex(args, mutex, philo, print);
	create_th(args, mutex, philo, th);
	detach_th(args, mutex, th);
	while (1)
	{
		dead_id = cheking_is_dead(philo, args);
		if (dead_id != -1)
			return (dead_id);
	}
}

void	detach_th(char **args, pthread_mutex_t *mutex,
		pthread_t *th)
{
	int	i;

	i = 0;
	while (i < ft_atoi(args[1]))
	{
		pthread_detach(th[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(args[1]))
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}

void	create_th(char **args, pthread_mutex_t *mutex, t_philo *philo,
		pthread_t *th)
{
	int	i;

	i = 0;
	while (i < ft_atoi(args[1]))
	{
		philo[i].left = &mutex[i];
		if (ft_atoi(args[1]) == 1)
		{
			one_philo(philo);
			return ;
		}
		if (i == ft_atoi(args[1]) - 1)
			philo[i].right = &mutex[0];
		else
			philo[i].right = &mutex[i + 1];
		if (pthread_create(&th[i], NULL, &lock_fork, (void *)&(philo[i])))
		{
			printf("Fail to create thread!\n");
			destroy(th, philo, mutex);
			return ;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	dead_id;

	dead_id = 0;
	if (ac < 5 || ac > 6 || ft_isdigit(av) == 0)
	{
		printf("Insert valid arguments!\n");
	}
	else
	{
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
			|| ft_atoi(av[4]) <= 0 || (av[5] != NULL && ft_atoi(av[5]) < 0))
			printf("Insert valid arguments!\n");
		else
		{
			if (create_philo(av, dead_id) == -1)
				return (0);
		}
	}
	return (0);
}
