/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:03:08 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/25 08:45:45 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_status(t_philo *philo, char *type, int index)
{
	static int	stop = 0;

	philo->index = index;
	sem_wait(philo->details->sem_msg);
	if (stop == 0)
	{
		if (philo->index == 1)
		{
			printf("%ld\t%s\n", get_time() - philo->details->start_time, type);
			stop = 1;
		}
		else if (index == 0 && !stop)
			printf("%ld\t%d %s\n", get_time() -
			philo->details->start_time, philo->id + 1, type);
		else if (index == 2)
		{
			printf("%ld\t%d %s\n", get_time() -
			philo->details->start_time, philo->id + 1, type);
			stop = 1;
		}
	}
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
