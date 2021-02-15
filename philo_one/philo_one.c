/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:27:01 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/15 16:57:54 by elahyani         ###   ########.fr       */
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
		if (pthread_mutex_unlock(philo->philo_mutex) < 0)
			break ;
		if (!philo->ph_is_eating && !philo->eat_cnt_reached && get_time() > philo->end)
		{
			if (pthread_mutex_lock(philo->details->mutex_msg) < 0)
				break ;
			printf("%ld\t%d died\n", get_time() - philo->details->start_time, philo->id + 1);
			pthread_mutex_unlock(philo->philo_mutex);
			pthread_mutex_unlock(philo->details->mutex_die);
			return (0);
		}
		pthread_mutex_unlock(philo->philo_mutex);
		usleep(1000);
	}
	return (0);
}

void	*check_count(void	*val)
{
	int			i;
	int			nbf;
	t_details	*details;

	i = 0;
	nbf = 0;
	details = (t_details *)val;
	while (1)
	{
		if (details->philo[i].eat_cnt_reached && (nbf++))
			i++;
		if (i == details->nb_of_philos)
			i = 0;
		if (nbf == details->nb_of_philos)
		{
			i = -1;
			while (++i < details->nb_of_philos)
				pthread_mutex_lock(details->philo[i].eat_mutex);
			break ;
		}
	}
	pthread_mutex_lock(details->mutex_msg);
	printf("%ld\treached eat count limit\n", get_time() - details->start_time);
	pthread_mutex_unlock(details->mutex_die);
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
		pthread_create(&thread, NULL, &philo_actions, (void *)(&details->philo[i]));
		pthread_detach(thread);
		usleep(100);
	}
	pthread_mutex_lock(details->mutex_die);
	pthread_mutex_unlock(details->mutex_die);
}

int		args_checker(int ac, char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_atoi(av[1]) < 2 || ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
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

void	ft_free(void *to_free)
{
	if (to_free)
		free(to_free);
}

void	clean_all(t_details *details)
{
	int	i;

	i = -1;
	while (++i < details->nb_of_philos)
	{
		pthread_mutex_destroy(&details->mutex_forks[i]);
		pthread_mutex_destroy(details->philo[i].philo_mutex);
		ft_free(details->philo[i].philo_mutex);
		pthread_mutex_destroy(details->philo[i].eat_mutex);
		ft_free(details->philo[i].eat_mutex);
	}
	ft_free(details->mutex_forks);
	pthread_mutex_destroy(details->mutex_msg);
	ft_free(details->mutex_msg);
	pthread_mutex_destroy(details->mutex_die);
	ft_free(details->mutex_die);
	free(details->philo);
	ft_free(details);
}

int		main(int ac, char **av)
{
	t_details	*details;

	details = malloc(sizeof(t_details));
	if (args_checker(ac, av))
		return (ft_error("error:\tbad arguments."));
	if (ft_init(details, ac, av))
		return (ft_error("error:\tinitialisation failed."));
	set_philos(details);
	clean_all(details);
	return (0);
}