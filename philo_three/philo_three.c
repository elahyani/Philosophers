/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:22:44 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/23 11:24:59 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	int			nbf;
	t_details	*details;

	nbf = 0;
	details = (t_details*)val;
	while (1)
	{
		sem_wait(details->philo[nbf].eat_cnt);
		nbf++;
		if (nbf == details->nb_of_philos)
			break ;
	}
	print_status(details->philo, ELR_A, 1);
	sem_post(details->sem_die);
	return (0);
}

void	*philo_actions(t_philo *philo)
{
	pthread_t	p_checker;

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
			sem_post(philo->eat_cnt);
			philo->eat_cnt_reached = 1;
			break ;
		}
	}
	return (0);
}

void	create_c_checker(t_details *details)
{
	pthread_t	c_checker;

	if (details->nb_must_eat > 0)
	{
		pthread_create(&c_checker, NULL, &check_count, (void*)details);
		pthread_detach(c_checker);
	}
}

void	set_philos(t_details *details)
{
	int			i;

	i = -1;
	create_c_checker(details);
	sem_wait(details->sem_die);
	details->start_time = get_time();
	while (++i < details->nb_of_philos)
	{
		details->philo[i].pid = fork();
		if ((details->philo[i].pid) < 0)
			return ;
		if (details->philo[i].pid == 0)
		{
			philo_actions(&details->philo[i]);
			exit(0);
		}
		usleep(100);
	}
	sem_wait(details->sem_die);
	sem_post(details->sem_die);
	i = -1;
	while (++i < details->nb_of_philos)
		kill(details->philo[i].pid, SIGKILL);
}
