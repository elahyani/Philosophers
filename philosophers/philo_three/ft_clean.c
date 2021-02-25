/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:25:17 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/24 09:14:57 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_free(void *to_free)
{
	if (to_free)
		free(to_free);
}

void	clean_philos(t_details *details)
{
	int		i;
	char	*name;

	i = 0;
	while (i < details->nb_of_philos)
	{
		name = ft_itoa(i + 1);
		sem_post(details->philo[i].philo_sem);
		sem_close(details->philo[i].philo_sem);
		sem_unlink(name);
		ft_free(name);
		i++;
	}
}

void	clean_all(t_details *details)
{
	int		i;

	i = -1;
	while (++i < details->nb_of_philos)
		sem_post(details->sem_forks);
	sem_close(details->sem_forks);
	sem_unlink("forks");
	sem_post(details->philo->eat_cnt);
	sem_close(details->philo->eat_cnt);
	sem_unlink("eat_cnt");
	clean_philos(details);
	sem_close(details->sem_msg);
	sem_unlink("msg");
	sem_close(details->sem_die);
	sem_unlink("die");
	ft_free(details->philo);
	ft_free(details);
}
