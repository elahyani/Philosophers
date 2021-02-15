/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:46:17 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/08 17:41:29 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t philosopher[5];
pthread_mutex_t forks[5];

void *func(void *nb)
{
	int		n;

	n = (int )nb;
	while (1)
	{
		printf("\nPhilosopher %d is thinking ",n);
		pthread_mutex_lock(&forks[n]); //when philosopher 5 is eating he takes fork 1 and fork 5
		pthread_mutex_lock(&forks[(n + 1) % 5]);
		printf("\nPhilosopher %d is eating ",n);
		sleep(3);
		pthread_mutex_unlock(&forks[n]);
		pthread_mutex_unlock(&forks[(n + 1) % 5]);
		printf("\nPhilosopher %d sleeping ",n);
		if (n == 5)
			exit (1);
	}
	return (0); 
}

int main(int ac, char **av)
{
	int		i;
	int		k;
	void	*msg;

	i = 0;
	while (++i <= 5)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			printf("\n Mutex initialization failed");
			exit(1);
		}
	}
	i = 0;
	while (++i <= 5)
	{
		if (pthread_create(&philosopher[i], NULL, func, (void *)(size_t )i))
		{
			printf("\n Thread creation error \n");
			exit(1);
		}
	}
	i = 0;
	while (++i <= 5)
	{
		if (pthread_join(philosopher[i], &msg))
		{
			printf("\n Thread join failed \n");
			exit(1);
		}
	}
	i = 0;
	while (++i <= 5)
	{
		if (pthread_mutex_destroy(&forks[i]))
		{
			printf("\n Mutex Destroyed \n");
			exit(1);
		}
	}
	return 0;
}


/*

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
	print_msg(get_time() - philo->ph_det->start_time, philo, FORK_A);
	pthread_mutex_lock(&philo->ph_det->fork[(philo->index + 1) % philo->ph_det->nb_of_philos]);
	print_msg(get_time() - philo->ph_det->start_time, philo, FORK_A);
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
	ph_det->fork = malloc(sizeof(pthread_mutex_t) * (ph_det->nb_of_philos));
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
		pthread_mutex_init(&philo->ph_det->fork[i], NULL);
	// pthread_mutex_init(&philo->ph_det->fd_stdout, NULL);
	// pthread_mutex_init(&philo->ph_det->die, NULL);
	// pthread_mutex_lock(&philo->ph_det->die);
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
	// while (++i < ph_det.nb_of_philos)
	// {
	// 	philo[i].index = i;
	// 	pthread_create(&ph_det.thread[i], NULL, &philo_action, &philo[i]);
	// 	pthread_detach(ph_det.thread[i]);
	// 	usleep(100);
	// }
	// pthread_mutex_lock(&ph_det.die);
	// pthread_mutex_unlock(&ph_det.die);
	return (0);
}

*/