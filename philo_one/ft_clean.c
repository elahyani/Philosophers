/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:07:08 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/15 17:08:35 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
