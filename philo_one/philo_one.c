/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:03:03 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/08 18:17:14 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// void	print_msg(int	tm, t_philo *philo, char *msg)
// {
// 	pthread_mutex_lock(&philo->ph_det->fd_stdout);
// 	ft_putnbr(tm);
// 	ft_putstr(" ");
// 	ft_putnbr(philo->index + 1);
// 	ft_putstr(msg);
// 	pthread_mutex_unlock(&philo->ph_det->fd_stdout);
// }

int		get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_det->forks[philo->index]);
	printf("%ld\t%d has taken a fork\n", get_time() - philo->ph_det->start_time, philo->index + 1);
	// print_msg(get_time() - philo->ph_det->start_time, philo, FORK_A);
	pthread_mutex_lock(&philo->ph_det->forks[(philo->index + 1) % philo->ph_det->nb_of_philos]);
	printf("%ld\t%d has taken a fork\n", get_time() - philo->ph_det->start_time, philo->index + 1);
	// print_msg(get_time() - philo->ph_det->start_time, philo, FORK_A);
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
		// philo_eating(philo);
		// philo_sleeping(philo);
	}
}

t_details	*ph_init(int id, t_details *prev, char **av, int ac)
{
	t_details	*ph_det;

	ph_det = malloc(sizeof(t_details));
	ph_det->id = id;
	ph_det->nb_of_philos = ft_atoi(av[1]);
	ph_det->time_to_die = ft_atoi(av[2]);
	ph_det->time_to_eat = ft_atoi(av[3]);
	ph_det->time_to_sleep = ft_atoi(av[4]);
	ph_det->nb_eat = ft_atoi(av[5]);
	ph_det->start_time = 0;
	ph_det->forks = malloc(sizeof(pthread_mutex_t) * (ph_det->nb_of_philos));
	ph_det->msg = malloc(sizeof(pthread_mutex_t));
	ph_det->die = malloc(sizeof(pthread_mutex_t));
	ph_det->next = NULL;
	ph_det->prev = prev;
	if (prev)
		prev->next = ph_det;
	return (ph_det);
}

t_details	*set_philos(t_philo *philo, int ph_num, char **av, int ac)
{
	int			i;
	t_details	*ph_det;

	i = -1;
	// ph_det = malloc(sizeof(t_details) * (ph_num + 1));
	ph_det = NULL;
	while (++i < ph_num)
	{
		ph_det = ph_init(i + 1, ph_det, av, ac);
		philo->ph_det = ph_det;
		philo->count = 0;
		ph_det = ph_det->next;
	}
	return (ph_det);
}

void	init_mutex(t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < philo->ph_det->nb_of_philos)
		pthread_mutex_init(&philo->ph_det->forks[i], NULL);
}

void	ft_init(t_philo *philo, char **av, int ac)
{
	philo = malloc(sizeof(t_philo));
	philo->count = ft_atoi(av[1]);
	init_mutex(philo);
	philo->ph_det = set_philos(philo, philo->count, av, ac);
	philo->ph_det->start_time = get_time();
}

int		main(int ac, char **av)
{
	int				i;
	t_philo			*philo;
	t_details		*ph_det;
	struct timeval	start;
	struct timeval	end;

	i = -1;
	ft_init(philo, av, ac);
	while (++i < ph_det->nb_of_philos)
	{
		philo[i].index = i;
		pthread_create(&ph_det->thread[i], NULL, &philo_action, &philo[i]);
		pthread_detach(ph_det->thread[i]);
		usleep(100);
	}
	pthread_mutex_lock(&ph_det->die);
	pthread_mutex_unlock(&ph_det->die);
	return (0);
}
