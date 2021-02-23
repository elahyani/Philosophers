/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:42:19 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/23 12:05:53 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	print_status(t_philo *philo, char *atype, int index)
{
	static int	stop = 0;

	philo->index = index;
	sem_wait(philo->details->sem_msg);
	if (stop == 0)
	{
		if (philo->index == 1)
		{
			printf("%ld\t%s\n", get_time() - philo->details->start_time, atype);
			stop = 1;
		}
		else if (index == 0 && !stop)
			printf("%ld\t%d %s\n", get_time() -
			philo->details->start_time, philo->id + 1, atype);
		else if (index == 2)
		{
			printf("%ld\t%d %s\n", get_time() -
			philo->details->start_time, philo->id + 1, atype);
			stop = 1;
			return ;
		}
	}
	sem_post(philo->details->sem_msg);
}
