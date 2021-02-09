/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:27:01 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/09 19:05:59 by elahyani         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d is eating\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
	usleep(philo->dtls->time_to_eat * 1000);
	philo->eat_cnt_times += 1;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d is sleeping\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
	pthread_mutex_unlock(&philo->dtls->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->dtls->mutex_forks[philo->right_fork]);
	usleep(philo->dtls->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->dtls->mutex_msg);
	printf("%ld\t%d is thinking\n", get_time() - philo->dtls->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->dtls->mutex_msg);
}

void	*philo_actions(void *val)
{
	t_philo	*philo;
	pthread_t	checker;

	philo = (t_philo *)val;
	while (1)
	{
		get_forks(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (0);
}

void	set_philos(t_dtls *dtls)
{
	int		i;
	pthread_t	eat_checker;

	i = -1;
	dtls->start_time = get_time();
	while (++i < dtls->nb_of_philos)
	{
		pthread_create(&dtls->thread, NULL, &philo_actions, (void *)(&dtls->philo[i]));
		pthread_detach(dtls->thread);
		usleep(100);
	}
	exit (0);
}

int		ft_mutexes_init(t_dtls *dtls)
{
	int		i;

	i = -1;
	pthread_mutex_init(&dtls->mutex_die, NULL);
	pthread_mutex_init(&dtls->mutex_msg, NULL);
	if (!(dtls->mutex_forks = malloc(sizeof(pthread_mutex_t) * (dtls->nb_of_philos))))
		return (1);
	while (++i < dtls->nb_of_philos)
		pthread_mutex_init(&dtls->mutex_forks[i], NULL);
	return (0);
}

int		ft_philos_init(t_dtls *dtls)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	philo = (t_philo *)dtls->philo;
	while (++i < dtls->nb_of_philos)
	{
		philo[i].ph_is_eating = 0;
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % dtls->nb_of_philos;
		philo[i].eat_cnt_times = 0;
		philo[i].dtls = dtls;
		pthread_mutex_init(&philo[i].mutex, NULL);
		pthread_mutex_init(&philo[i].mutex_eat, NULL);
		pthread_mutex_lock(&philo[i].mutex_eat);
	}
	dtls->philo = philo;
	return (0);
}

int		ft_init(t_dtls *dtls, int ac, char **av)
{
	// dtls = malloc(sizeof(t_dtls *));
	dtls->nb_of_philos = ft_atoi(av[1]);
	dtls->time_to_die = ft_atoi(av[2]);
	dtls->time_to_eat = ft_atoi(av[3]);
	dtls->time_to_sleep = ft_atoi(av[4]);
	dtls->nb_must_eat = 0;
	(ac == 6) ? dtls->nb_must_eat = ft_atoi(av[5]) : 0;
	dtls->mutex_forks = NULL;
	if (!(dtls->philo =  malloc(sizeof(t_philo) * (dtls->nb_of_philos + 1))))
		return (1);
	if (ft_philos_init(dtls))
		return (1);
	if (ft_mutexes_init(dtls))
		return (1);
	return (0);
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