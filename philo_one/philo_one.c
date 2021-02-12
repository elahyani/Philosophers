/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:27:01 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/12 12:03:35 by elahyani         ###   ########.fr       */
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

// void	*ph_checker(void	*val)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)val;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->philo_mutex);
// 		if (!philo->ph_is_eating && get_time() > philo->end)
// 		{
// 			printf("%ld\t%d died\n", get_time() - philo->dtls->start_time, philo->id + 1);
// 			pthread_mutex_unlock(&philo->philo_mutex);
// 			pthread_mutex_unlock(&philo->dtls->mutex_die);
// 			return (0);
// 		}
// 		pthread_mutex_unlock(&philo->philo_mutex);
// 		usleep(100);
// 	}
// 	return (0);
// }

void	*check_count(void	*val)
{
	t_dtls	*dtls;
	t_philo	*philo;
	int		i;
	int		j;

	i = -1;
	dtls = (t_dtls *)val;
	philo = dtls->philo;
	printf("----------> %d\n", dtls->philo->eat_cnt_reached);
	
	if (!dtls->nb_must_eat && dtls->philo->eat_cnt_reached)
	{
		while (++i < dtls->nb_must_eat)
			pthread_mutex_lock(&dtls->philo->eat_mutex);
	}
	printf("%ld\treached eat count limit\n", get_time() - dtls->start_time);
	pthread_mutex_unlock(&dtls->mutex_die);
	return (0);
}

void	*philo_actions(void *val)
{
	t_philo	*philo;
	pthread_t	p_checker;

	philo = (t_philo *)val;
	philo->start = get_time();
	philo->end = philo->start + philo->dtls->time_to_die;
	// pthread_create(&p_checker, NULL, &ph_checker, (void *)philo);
	// pthread_detach(p_checker);
	while (1)
	{
		get_forks(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		if (philo->dtls->nb_must_eat == 0)
		{
			philo->eat_cnt_reached = 1;
			break ;
		}
	}
	return (0);
}

void	set_philos(t_dtls *dtls)
{
	int		i;
	pthread_t	c_cheker;
	
	i = -1;
	if (dtls->nb_must_eat > 0)
	{
		pthread_create(&c_cheker, NULL, &check_count, (void*)dtls);
		pthread_detach(c_cheker);
	}
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