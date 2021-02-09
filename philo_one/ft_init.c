/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:10:10 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/09 19:10:38 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_mutexes_init(t_dtls *dtls)
{
	int		i;

	i = -1;
	pthread_mutex_init(&dtls->mutex_die, NULL);
	pthread_mutex_init(&dtls->mutex_msg, NULL);
	if (!(dtls->mutex_forks = malloc(sizeof(pthread_mutex_t) * (dtls->nb_of_philos))))
		return (1);
	while (++i < dtls->nb_of_philos)
		pthread_mutex_init(&dtls->mutex_forks[i], NULL);
	return (0);
}

int		ft_philos_init(t_dtls *dtls)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	philo = (t_philo *)dtls->philo;
	while (++i < dtls->nb_of_philos)
	{
		philo[i].ph_is_eating = 0;
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % dtls->nb_of_philos;
		philo[i].eat_cnt_times = 0;
		philo[i].dtls = dtls;
		pthread_mutex_init(&philo[i].mutex, NULL);
		pthread_mutex_init(&philo[i].mutex_eat, NULL);
		pthread_mutex_lock(&philo[i].mutex_eat);
	}
	dtls->philo = philo;
	return (0);
}

int		ft_init(t_dtls *dtls, int ac, char **av)
{
	// dtls = malloc(sizeof(t_dtls *));
	dtls->nb_of_philos = ft_atoi(av[1]);
	dtls->time_to_die = ft_atoi(av[2]);
	dtls->time_to_eat = ft_atoi(av[3]);
	dtls->time_to_sleep = ft_atoi(av[4]);
	dtls->nb_must_eat = 0;
	(ac == 6) ? dtls->nb_must_eat = ft_atoi(av[5]) : 0;
	dtls->mutex_forks = NULL;
	if (!(dtls->philo =  malloc(sizeof(t_philo) * (dtls->nb_of_philos + 1))))
		return (1);
	if (ft_philos_init(dtls))
		return (1);
	if (ft_mutexes_init(dtls))
		return (1);
	return (0);
}
