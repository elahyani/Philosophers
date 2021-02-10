/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:27:01 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/10 10:17:06 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_error(char	*err_msg)
{
	if (err_msg)
		printf("%s\n", err_msg);
	return (1);
}

long	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	*philo_actions(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	philo->start = get_time();
	philo->end = philo->start + philo->dtls->time_to_die;
	while (1)
	{
		get_forks(philo);
		philo_eating(philo);
		philo_sleeping(philo);
	}
	return (0);
}

void	set_philos(t_dtls *dtls)
{
	int		i;

	i = -1;
	// dtls->start_time = get_time();
	pthread_mutex_lock(&dtls->mutex_die);
	while (++i < dtls->nb_of_philos)
	{
		pthread_create(&dtls->thread, NULL, &philo_actions, (void *)(&dtls->philo[i]));
		pthread_detach(dtls->thread);
		usleep(100);
	}
	pthread_mutex_lock(&dtls->mutex_die);
	pthread_mutex_unlock(&dtls->mutex_die);
}

int		args_checker(int ac, char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_atoi(av[1]) < 2)
		return (1);
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_dtls	dtls;
	
	if (args_checker(ac, av))
		return (ft_error("error:\tbad arguments."));
	if (ft_init(&dtls, ac, av))
		return (ft_error("error:\tinitialisation failed."));
	set_philos(&dtls);
	return (0);
}