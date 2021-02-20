/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:51:37 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/20 12:33:17 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		ft_init_semaphores(t_details *details)
{
	sem_unlink("forks");
	details->sem_forks = sem_open("forks", O_CREAT, 0666,
	details->nb_of_philos);
	sem_unlink("die");
	details->sem_die = sem_open("die", O_CREAT, 0666, 1);
	sem_unlink("msg");
	details->sem_msg = sem_open("msg", O_CREAT, 0666, 1);
}

t_philo		*ft_philos_init(t_details *details)
{
	int			i;
	t_philo		*philo;
	char		*name;

	i = 0;
	philo = details->philo;
	while (i < details->nb_of_philos)
	{
		philo[i].ph_is_eating = 0;
		philo[i].id = i;
		philo[i].nb_must_eat = details->nb_must_eat;
		philo[i].eat_cnt_reached = 0;
		philo[i].details = details;
		name = ft_itoa(i + 1);
		sem_unlink(name);
		philo[i].philo_sem = sem_open(name, O_CREAT, 0666, 1);
		free(name);
		i++;
	}
	return (philo);
}

int			ft_init(t_details *details, int ac, char **av)
{
	details->nb_of_philos = ft_atoi(av[1]);
	details->time_to_die = ft_atoi(av[2]);
	details->time_to_eat = ft_atoi(av[3]);
	details->time_to_sleep = ft_atoi(av[4]);
	details->nb_must_eat = ac == 6 ? ft_atoi(av[5]) : -1;
	details->sem_forks = NULL;
	details->stop = 0;
	details->start_time = get_time();
	if (!(details->philo =
		malloc(sizeof(t_philo) * (details->nb_of_philos + 1))))
		return (1);
	details->philo = ft_philos_init(details);
	ft_init_semaphores(details);
	return (0);
}
