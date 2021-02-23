/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:23:23 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/23 11:43:34 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	get_forks(t_philo *philo)
{
	sem_wait(philo->details->sem_forks);
	print_status(philo, FORK_A, 0);
	sem_wait(philo->details->sem_forks);
	print_status(philo, FORK_A, 0);
}

void	philo_eating(t_philo *philo)
{
	if (sem_wait(philo->philo_sem) < 0)
		exit(1);
	philo->ph_is_eating = 1;
	philo->start = get_time();
	philo->end = philo->start + philo->details->time_to_die;
	print_status(philo, EAT_A, 0);
	usleep(philo->details->time_to_eat * 1000);
	if (philo->nb_must_eat != -1)
		philo->nb_must_eat -= 1;
	philo->ph_is_eating = 0;
	if (sem_post(philo->philo_sem) < 0)
		exit(1);
	sem_post(philo->details->sem_forks);
	sem_post(philo->details->sem_forks);
}

void	philo_sleeping(t_philo *philo)
{
	print_status(philo, SLEEP_A, 0);
	usleep(philo->details->time_to_sleep * 1000);
	print_status(philo, THINK_A, 0);
}
