/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:02:08 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/23 12:12:02 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_free(void *to_free)
{
	if (to_free)
		free(to_free);
}

void	clean_all(t_details *details)
{
	int		i;
	char	*name;

	i = -1;
	while (++i < details->nb_of_philos)
		sem_post(details->sem_forks);
	sem_close(details->sem_forks);
	sem_unlink("forks");
	i = -1;
	while (++i < details->nb_of_philos)
	{
		name = ft_itoa(i + 1);
		sem_post(details->philo[i].philo_sem);
		sem_close(details->philo[i].philo_sem);
		sem_unlink(name);
		ft_free(name);
	}
	sem_close(details->sem_msg);
	sem_unlink("msg");
	sem_close(details->sem_die);
	sem_unlink("die");
	ft_free(details->philo);
	ft_free(details);
}
