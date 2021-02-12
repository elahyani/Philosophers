/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:07:35 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/12 11:37:48 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->dtls->mutex_forks[philo->left_fork]);
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d has taking a fork\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
	pthread_mutex_lock(&philo->dtls->mutex_forks[philo->right_fork]);
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d has taking a fork\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->ph_is_eating = 1;
	philo->start = get_time();
	philo->end = philo->start + philo->dtls->time_to_die;
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d is eating\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
	usleep(philo->dtls->time_to_eat * 1000);
	(philo->dtls->nb_must_eat != 0) ? philo->dtls->nb_must_eat -= 1 : 0;
	philo->ph_is_eating = 0;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(&philo->dtls->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->dtls->mutex_forks[philo->right_fork]);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d is sleeping\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
	usleep(philo->dtls->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d is thinking\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
}
