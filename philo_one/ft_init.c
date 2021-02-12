/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:10:10 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/12 17:00:39 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_mutexes_init(t_details *details)
{
	int		i;

	i = -1;
	pthread_mutex_init(&details->mutex_msg, NULL);
	pthread_mutex_init(&details->mutex_die, NULL);
	if (!(details->mutex_forks =
			malloc(sizeof(pthread_mutex_t) * (details->nb_of_philos))))
		return (1);
	while (++i < details->nb_of_philos)
		pthread_mutex_init(&details->mutex_forks[i], NULL);
	return (0);
}

t_philo		*ft_philos_init(t_details *details)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = details->philo;
	while (++i < details->nb_of_philos)
	{
		philo[i].ph_is_eating = 0;
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % details->nb_of_philos;
		philo[i].eat_cnt_reached = 0;
		philo[i].details = details;
		pthread_mutex_init(&philo[i].philo_mutex, NULL);
		pthread_mutex_init(&philo[i].eat_mutex, NULL);
		pthread_mutex_lock(&philo[i].eat_mutex);
	}
	return (philo);
}

int			ft_init(t_details *details, int ac, char **av)
{
	details->nb_of_philos = ft_atoi(av[1]);
	details->time_to_die = ft_atoi(av[2]);
	details->time_to_eat = ft_atoi(av[3]);
	details->time_to_sleep = ft_atoi(av[4]);
	details->nb_must_eat = 0;
	(ac == 6) ? details->nb_must_eat = ft_atoi(av[5]) : -1;
	details->mutex_forks = NULL;
	details->start_time = get_time();
	if (!(details->philo =
			malloc(sizeof(t_philo) * (details->nb_of_philos + 1))))
		return (1);
	details->philo = ft_philos_init(details);
	if (ft_mutexes_init(details))
		return (1);
	return (0);
}
