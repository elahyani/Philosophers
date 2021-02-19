/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:02:08 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/19 19:10:10 by elahyani         ###   ########.fr       */
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

	i = -1;
	sem_unlink("forks");
	sem_close(details->sem_forks);
	sem_unlink("msg");
	sem_close(details->sem_msg);
	sem_unlink("die");
	sem_close(details->sem_die);
	while (++i < details->nb_of_philos)
	{
		sem_unlink(ft_itoa(i + 1));
		sem_close(details->philo[i].philo_sem);
	}
	ft_free(details->philo);
	ft_free(details);
}