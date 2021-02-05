/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:51:05 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/05 12:44:13 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int			id;
	int			nb_eat;
	int			nb_of_philos;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	time_to_die;
}				t_philo;


pthread_mutex_t	mutex;
int				ft_atoi(const char *str);

#endif