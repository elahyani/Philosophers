/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:27:01 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/12 19:20:21 by elahyani         ###   ########.fr       */
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

void	*ph_checker(void	*val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	while (1)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		if (!philo->ph_is_eating && get_time() > philo->end)
		{
			pthread_mutex_lock(&philo->details->mutex_msg);
			printf("%ld\t%d died\n", get_time() - philo->details->start_time, philo->id + 1);
			pthread_mutex_unlock(&philo->philo_mutex);
			pthread_mutex_unlock(&philo->details->mutex_die);
			return (0);
		}
		pthread_mutex_unlock(&philo->philo_mutex);
		usleep(1000);
	}
	return (0);
}

void	*check_count(void	*val)
{
	t_details	*details;
	int		i;
	int		j;
	int		nbf;

	nbf = 0;
	i = 0;
	details = (t_details *)val;
	while (1)
	{
		if (details->philo[i].eat_cnt_reached)
		{
			nbf++;
			printf("nbf = %d\n",nbf);
			details->philo[i].eat_cnt_reached = 0;
			i++;
		}
		if (i == details->nb_of_philos)
			i = 0;
		if (nbf == details->nb_of_philos)
		{
			i = -1;
			while (++i < details->nb_of_philos)
				pthread_mutex_lock(&details->philo[i].eat_mutex);
			puts("rule 1");
			break ;
		}
	}
	pthread_mutex_lock(&details->mutex_msg);
	printf("%ld\treached eat count limit\n", get_time() - details->start_time);
	pthread_mutex_unlock(&details->mutex_msg);
	pthread_mutex_unlock(&details->mutex_die);
	return (0);
}

void	*philo_actions(void *val)
{
	t_philo	*philo;
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
		usleep(100);
	}
	return (0);
}

void	set_philos(t_details *details)
{
	int		i;
	pthread_t	c_cheker;
	
	i = -1;
	if (details->nb_must_eat > 0)
	{
		pthread_create(&c_cheker, NULL, &check_count, (void*)details);
		pthread_detach(c_cheker);
	}
	pthread_mutex_lock(&details->mutex_die);
	while (++i < details->nb_of_philos)
	{
		pthread_create(&details->thread, NULL, &philo_actions, (void *)(&details->philo[i]));
		pthread_detach(details->thread);
		usleep(100);
	}
	pthread_mutex_lock(&details->mutex_die);
	pthread_mutex_unlock(&details->mutex_die);
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
	t_details	details;

	if (args_checker(ac, av))
		return (ft_error("error:\tbad arguments."));
	if (ft_init(&details, ac, av))
		return (ft_error("error:\tinitialisation failed."));
	set_philos(&details);
	return (0);
}