/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:23:23 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/22 11:26:15 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	print_status(t_philo *philo, char *atype, int index)
{
	philo->index = index;
	sem_wait(philo->details->sem_msg);
	if (philo->index == 1)
		printf("%ld\t%s\n", get_time() - philo->details->start_time, atype);
	else
	{
		if (!philo->details->stop)
			printf("%ld\t%d %s\n", get_time() - philo->details->start_time, philo->id + 1, atype);
	}
	if (philo->index != 2)
		sem_post(philo->details->sem_msg);
}

void	get_forks(t_philo *philo)
{
	sem_wait(philo->details->sem_forks);
	print_status(philo, FORK_A, 0);
	sem_wait(philo->details->sem_forks);
	print_status(philo, FORK_A, 0);
}

void	philo_eating(t_philo *philo)
{
	sem_wait(philo->philo_sem);
	philo->ph_is_eating = 1;
	philo->start = get_time();
	philo->end = philo->start + philo->details->time_to_die;
	print_status(philo, EAT_A, 0);
	usleep(philo->details->time_to_eat * 1000);
	if (philo->nb_must_eat != -1)
		philo->nb_must_eat -= 1;
	philo->ph_is_eating = 0;
	sem_post(philo->philo_sem);
	sem_post(philo->details->sem_forks);
	sem_post(philo->details->sem_forks);
}

void	philo_sleeping(t_philo *philo)
{
	print_status(philo, SLEEP_A, 0);
	usleep(philo->details->time_to_sleep * 1000);
	print_status(philo, THINK_A, 0);
}
