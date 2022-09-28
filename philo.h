/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:11:26 by sabazyan          #+#    #+#             */
/*   Updated: 2022/09/28 11:33:29 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct t_data {
	int				num;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long long int	ms_die;
	long long int	ms_eat;
	long long int	ms_sleep;
	int				count;
	pthread_mutex_t	*print;
	int				*is_dead;
}	t_philo;
//utils.c
int				ft_atoi(char *str);
long long int	get_time(void);
int				ft_isdigit(char **s);
//lock_fork.c
void			four_args(t_philo *ph, long long int start, long long int time);
void			five_args(t_philo *ph, long long int start, long long int time);
int				forks(t_philo *ph, long long int start, long long int time);
void			init_mutex(char **args, pthread_mutex_t *mutex, t_philo *philo,
					pthread_mutex_t	print);
//main.c
int				create_philo(char **args, int dead_id);
void			detach_th(char **args, pthread_mutex_t *mutex, pthread_t *th);
void			create_th(char **args, pthread_mutex_t *mutex, t_philo *philo,
					pthread_t *th);
//philo_utils.c
void			print_actions(t_philo *philo, char *message,
					long long int time, int num);
void			one_philo(t_philo *ph);
void			destroy(pthread_t *th, t_philo *philo, pthread_mutex_t	*mutex);
int				cheking_is_dead(t_philo *philo, char **av);
#endif
