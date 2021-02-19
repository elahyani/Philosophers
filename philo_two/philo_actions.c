/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:03:08 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/19 18:51:36 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	get_forks(t_philo *philo)
{
	sem_wait(philo->details->sem_forks);

	sem_wait(philo->details->sem_msg);
	printf("%ld\t%d %s\n", get_time() - philo->details->start_time, philo->id + 1, FORK_A);
	sem_post(philo->details->sem_msg);
	
	sem_wait(philo->details->sem_forks);

	sem_wait(philo->details->sem_msg);
	printf("%ld\t%d %s\n", get_time() - philo->details->start_time, philo->id + 1, FORK_A);
	sem_post(philo->details->sem_msg);
}

void	philo_eating(t_philo *philo)
{
	sem_wait(philo->philo_sem);

	philo->ph_is_eating = 1;
	philo->start = get_time();
	philo->end = philo->start + philo->details->time_to_die;

	sem_wait(philo->details->sem_msg);
	printf("%ld\t%d %s\n", get_time() - philo->details->start_time, philo->id + 1, EAT_A);
	sem_post(philo->details->sem_msg);

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
	sem_wait(philo->details->sem_msg);
	printf("%ld\t%d %s\n", get_time() - philo->details->start_time, philo->id + 1, SLEEP_A);
	sem_post(philo->details->sem_msg);

	usleep(philo->details->time_to_sleep * 1000);

	sem_wait(philo->details->sem_msg);
	printf("%ld\t%d %s\n", get_time() - philo->details->start_time, philo->id + 1, THINK_A);
	sem_post(philo->details->sem_msg);
}
