/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:17:36 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/16 09:52:01 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ph_checker(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	while (1)
	{
		if (pthread_mutex_unlock(philo->philo_mutex) < 0)
			break ;
		if (!philo->ph_is_eating && !philo->eat_cnt_reached &&
		get_time() > philo->end)
		{
			if (pthread_mutex_lock(philo->details->mutex_msg) < 0)
				break ;
			printf("%ld\t%d died\n", get_time() - philo->details->start_time,
			philo->id + 1);
			pthread_mutex_unlock(philo->philo_mutex);
			pthread_mutex_unlock(philo->details->mutex_die);
			return (0);
		}
		pthread_mutex_unlock(philo->philo_mutex);
		usleep(1000);
	}
	return (0);
}

void	*check_count(void *val)
{
	int			i;
	int			nbf;
	t_details	*details;

	i = 0;
	nbf = 0;
	details = (t_details *)val;
	while (1)
	{
		if (i == details->nb_of_philos)
			i = 0;
		if (details->philo[i].eat_cnt_reached == 1 &&
		details->philo[i].nb_must_eat == 0)
		{
			nbf++;
			details->philo[i].nb_must_eat = -1;
		}
		if (nbf == details->nb_of_philos)
			break ;
		i++;
	}
	pthread_mutex_lock(details->mutex_msg);
	printf("%ld\treached eat count limit\n", get_time() - details->start_time);
	pthread_mutex_unlock(details->mutex_die);
	return (0);
}

void	*philo_actions(void *val)
{
	t_philo		*philo;
	pthread_t	p_checker;

	philo = (t_philo *)val;
	philo->start = get_time();
	philo->end = philo->start + philo->details->time_to_die;
	pthread_create(&p_checker, NULL, &ph_checker, (void *)philo);
	pthread_detach(p_checker);
	while (1)
	{
		get_forks(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		if (philo->nb_must_eat == 0)
		{
			philo->eat_cnt_reached = 1;
			break ;
		}
	}
	return (0);
}

void	set_philos(t_details *details)
{
	int			i;
	pthread_t	thread;
	pthread_t	c_cheker;

	i = -1;
	if (details->nb_must_eat > 0)
	{
		pthread_create(&c_cheker, NULL, &check_count, (void*)details);
		pthread_detach(c_cheker);
	}
	pthread_mutex_lock(details->mutex_die);
	while (++i < details->nb_of_philos)
	{
		pthread_create(&thread, NULL, &philo_actions,
		(void *)(&details->philo[i]));
		pthread_detach(thread);
		usleep(100);
	}
	pthread_mutex_lock(details->mutex_die);
	pthread_mutex_unlock(details->mutex_die);
}
