/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:10:10 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/12 12:01:39 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_mutexes_init(t_dtls *dtls)
{
	int		i;

	i = -1;
	pthread_mutex_init(&dtls->mutex_msg, NULL);
	pthread_mutex_init(&dtls->mutex_die, NULL);
	if (!(dtls->mutex_forks = malloc(sizeof(pthread_mutex_t) * (dtls->nb_of_philos))))
		return (1);
	while (++i < dtls->nb_of_philos)
		pthread_mutex_init(&dtls->mutex_forks[i], NULL);
	return (0);
}

t_philo		*ft_philos_init(t_dtls *dtls)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	philo = dtls->philo;
	while (++i < dtls->nb_of_philos)
	{
		philo[i].ph_is_eating = 0;
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % dtls->nb_of_philos;
		philo[i].eat_cnt_reached = 0;
		philo[i].dtls = dtls;
		pthread_mutex_init(&philo[i].philo_mutex, NULL);
		pthread_mutex_init(&philo[i].eat_mutex, NULL);
		pthread_mutex_lock(&philo[i].eat_mutex);
	}
	return (philo);
}

int		ft_init(t_dtls *dtls, int ac, char **av)
{
	dtls->nb_of_philos = ft_atoi(av[1]);
	dtls->time_to_die = ft_atoi(av[2]);
	dtls->time_to_eat = ft_atoi(av[3]);
	dtls->time_to_sleep = ft_atoi(av[4]);
	dtls->nb_must_eat = 0;
	(ac == 6) ? dtls->nb_must_eat = ft_atoi(av[5]) : 0;
	dtls->mutex_forks = NULL;
	dtls->start_time = get_time();
	if (!(dtls->philo =  malloc(sizeof(t_philo) * (dtls->nb_of_philos + 1))))
		return (1);
	dtls->philo = ft_philos_init(dtls);
	if (ft_mutexes_init(dtls))
		return (1);
	return (0);
}
