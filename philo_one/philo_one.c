/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:03:03 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/07 11:58:17 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_msg(int	tm, t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->ph_det->fd_stdout);
	ft_putnbr(tm);
	ft_putstr(" ");
	ft_putnbr(philo->index + 1);
	ft_putstr(msg);
	pthread_mutex_unlock(&philo->ph_det->fd_stdout);
}

int		get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_det->fork[philo->index]);
	print_msg(get_time() - philo->ph_det->start, philo, FORK_A);
	pthread_mutex_lock(&philo->ph_det->fork[(philo->index + 1) % philo->ph_det->nb_of_philos]);
	print_msg(get_time() - philo->ph_det->start, philo, FORK_A);
}

// void	philo_eating(t_philo *philo)
// {
// 	print_msg(get_time() - philo->ph_det->start, philo, EAT_A);
	
// }

void	*philo_action(void	*val)
{
	int					start_time;
	t_philo				*philo;
	struct timeval		bf_eat;

	philo = (t_philo *)val;
	//start_time = 1;
	while (1)
	{
		get_forks(philo);
		//philo_eating(philo);
		//philo_sleeping(philo);
	}
}

void	set_philos(t_philo *philo, t_ph_det *ph_det)
{
	int		i;

	i = -1;
	while (++i < ph_det->nb_of_philos)
	{
		philo[i].ph_det = ph_det;
		philo[i].count = 0;
	}
}

void	init_mutex(t_ph_det *ph_det)
{
	int		i;

	i = -1;
	while (++i < ph_det->nb_of_philos)
		pthread_mutex_init(&ph_det->fork[i], NULL);
	pthread_mutex_init(&ph_det->fd_stdout, NULL);
	pthread_mutex_init(&ph_det->die, NULL);
	pthread_mutex_lock(&ph_det->die);
}

void	ft_init(t_philo **philo, t_ph_det *ph_det, char **av)
{
	ph_det = malloc(sizeof(t_ph_det));
	*philo = malloc(sizeof(t_philo));
	ph_det->nb_of_philos = ft_atoi(av[1]);
	ph_det->time_to_die = ft_atoi(av[2]);
	ph_det->time_to_eat = ft_atoi(av[3]);
	ph_det->time_to_sleep = ft_atoi(av[4]);
	ph_det->nb_eat = ft_atoi(av[5]);
	set_philos(*philo, ph_det);
	ph_det->fork = malloc(sizeof(pthread_mutex_t) * (ph_det->id));
	ph_det->thread = malloc(sizeof(pthread_mutex_t) * (ph_det->id));
	ph_det->status = malloc(sizeof(void *) * (ph_det->id));
	init_mutex(ph_det);
	ph_det->start = get_time();
}

int		main(int ac, char **av)
{
	int				i;
	long int		count;
	t_philo			*philo;
	t_ph_det		ph_det;
	struct timeval	start;
	struct timeval	end;
	
	i = -1;
	ft_init(&philo, &ph_det, av);
	while (++i < ph_det.nb_of_philos)
	{
		philo[i].index = i;
		pthread_create(&ph_det.thread[i], NULL, &philo_action, &philo[i]);
		pthread_detach(ph_det.thread[i]);
		usleep(100);
	}
	pthread_mutex_lock(&ph_det.die);
	pthread_mutex_unlock(&ph_det.die);
	return (0);
}
