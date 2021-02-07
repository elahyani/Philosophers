/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:51:05 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/07 11:50:48 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK_A		" has taken a fork\n"
# define DIE_A		" died\n"
# define EAT_A		" is eating\n"
# define SLEEP_A	" is sleeping\n"
# define THINK_A	" is thinking\n"

typedef struct			s_ph_det
{
	int					id;
	int					start;
	int					nb_eat;
	int					nb_of_philos;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	void				**status;
	pthread_t			*thread;
	pthread_mutex_t		*fork;
	pthread_mutex_t		die;
	pthread_mutex_t		fd_stdout;
}						t_ph_det;

typedef struct			s_philo
{
	struct s_ph_det		*ph_det;
	int					index;
	int					count;
}						t_philo;


int						ft_atoi(const char *str);
int						ft_strlen(const char *s);
void					ft_putstr(char *s);
void					*ft_memset(void *b, int c, size_t len);
void					ft_putnbr(int n);

#endif