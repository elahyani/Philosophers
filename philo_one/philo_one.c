/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:03:03 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/05 12:58:37 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philo_action(t_philo **philo)
{
	int			i;
	int			nb_eat;
	long int	tte;
	long int	tts;

	i = 0;
	tte = (*philo)->time_to_eat;
	tts = (*philo)->time_to_sleep;
	printf("eat time: %ld\n", tte);
	printf("sleep time: %ld\n", tts);
	printf("die time: %ld\n", (*philo)->time_to_die);
	// while (tte < (*philo)->time_to_die)
	// {
	// 	pthread_mutex_lock(&mutex);
	// 	printf("philo %d eating\n", (*philo)->id);
	// 	//usleep(100000);
	// 	pthread_mutex_unlock(&mutex);
	// 	tte++;
	// }
}

int		main(int ac, char **av)
{
	int			i;
	long int	count;
	t_philo		*philo;
	
	i = 0;
	philo = malloc(sizeof(t_philo));
	philo->nb_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->nb_eat = ft_atoi(av[5]);
	pthread_t	th[philo->nb_of_philos];
	struct timeval	start;
	struct timeval	end;
	
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&start, NULL);
	count = start.tv_sec * 1000000 + start.tv_usec;
	philo->time_to_die += count;
	while (i < philo->nb_of_philos)
	{
		philo->id = i;
		pthread_create(th + i, NULL, (void * (*)(void *)) philo_action, &philo);
		i++;
	}
	i = 0;
	while (i < philo->nb_of_philos)
	{
		pthread_join(th[i], NULL);
		i++;
		
	}
	// while (count < philo->time_to_die)
	// {
	// 	printf("philoeating...\n");
	// 	usleep(100000);
	// 	count++;
	// }
	pthread_mutex_destroy(&mutex);
	// printf("Philo Die...\n");
	// printf("nb philos: %d\n", nb_of_philos);
	// printf("die time: %ld\n", time_to_die);
	// printf("eat time: %ld\n", time_to_eat);
	// printf("sleep time: %ld\n", time_to_sleep);
	// printf("nb eat: %d\n", nb_eat);
	return (0);
}
