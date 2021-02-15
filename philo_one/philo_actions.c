/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:07:35 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/15 17:23:15 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->details->mutex_forks[philo->left_fork]);
	pthread_mutex_lock(philo->details->mutex_msg);
	printf("%ld\t%d %s\n", get_time() -
	philo->details->start_time, philo->id + 1, FORK_A);
	pthread_mutex_unlock(philo->details->mutex_msg);
	pthread_mutex_lock(&philo->details->mutex_forks[philo->right_fork]);
	pthread_mutex_lock(philo->details->mutex_msg);
	printf("%ld\t%d %s\n", get_time() -
	philo->details->start_time, philo->id + 1, FORK_A);
	pthread_mutex_unlock(philo->details->mutex_msg);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_mutex);
	philo->ph_is_eating = 1;
	philo->start = get_time();
	philo->end = philo->start + philo->details->time_to_die;
	pthread_mutex_lock(philo->details->mutex_msg);
	printf("%ld\t%d %s\n", get_time() -
	philo->details->start_time, philo->id + 1, EAT_A);
	pthread_mutex_unlock(philo->details->mutex_msg);
	usleep(philo->details->time_to_eat * 1000);
	if (philo->nb_must_eat != -1)
		philo->nb_must_eat -= 1;
	philo->ph_is_eating = 0;
	pthread_mutex_unlock(philo->philo_mutex);
	pthread_mutex_unlock(philo->eat_mutex);
	pthread_mutex_unlock(&philo->details->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->details->mutex_forks[philo->right_fork]);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->details->mutex_msg);
	printf("%ld\t%d %s\n", get_time() -
	philo->details->start_time, philo->id + 1, SLEEP_A);
	pthread_mutex_unlock(philo->details->mutex_msg);
	usleep(philo->details->time_to_sleep * 1000);
	pthread_mutex_lock(philo->details->mutex_msg);
	printf("%ld\t%d %s\n", get_time() -
	philo->details->start_time, philo->id + 1, THINK_A);
	pthread_mutex_unlock(philo->details->mutex_msg);
}
