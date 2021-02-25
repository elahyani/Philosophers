/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:55:17 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/23 09:48:59 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*ph_checker(void *val)
{
	t_philo		*philo;

	philo = (t_philo *)val;
	while (1)
	{
		if (sem_wait(philo->philo_sem) < 0)
			break ;
		if (!philo->ph_is_eating && !philo->eat_cnt_reached &&
		get_time() > philo->end)
		{
			print_status(philo, DIE_A, 2);
			sem_post(philo->philo_sem);
			sem_post(philo->details->sem_die);
			break ;
		}
		if (sem_post(philo->philo_sem) < 0)
			break ;
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
	details = (t_details*)val;
	while (1)
	{
		i == details->nb_of_philos ? i = 0 : 0;
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
	print_status(details->philo, ELR_A, 1);
	sem_post(details->sem_die);
	return (0);
}

void	*philo_actions(void *val)
{
	t_philo		*philo;
	pthread_t	p_checker;

	philo = (t_philo *)val;
	philo->start = get_time();
	philo->end = philo->start + philo->details->time_to_die;
	pthread_create(&p_checker, NULL, &ph_checker, (void*)philo);
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
	pthread_t	c_checker;

	i = -1;
	if (details->nb_must_eat > 0)
	{
		pthread_create(&c_checker, NULL, &check_count, (void*)details);
		pthread_detach(c_checker);
	}
	sem_wait(details->sem_die);
	details->start_time = get_time();
	while (++i < details->nb_of_philos)
	{
		pthread_create(&thread, NULL, &philo_actions,
		(void*)(&details->philo[i]));
		pthread_detach(thread);
		usleep(100);
	}
	sem_wait(details->sem_die);
	sem_post(details->sem_die);
}
