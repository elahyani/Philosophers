/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:51:05 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/10 10:05:45 by elahyani         ###   ########.fr       */
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

typedef struct		s_dtls
{
	int				nb_must_eat;
	long			start_time;
	int				nb_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_msg;
	struct s_philo	*philo;
}					t_dtls;

typedef struct		s_philo
{
	int				id;
	long			last_time_eat;
	long			end;
	long			start;
	int				is_eating;
	int				ph_is_eating;
	int				left_fork;
	int				right_fork;
	int				index;
	int				eat_cnt_times;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_eat;
	struct s_dtls	*dtls;
}					t_philo;

int					ft_atoi(const char *str);
int					ft_strlen(const char *s);
void				ft_putstr(char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putnbr(int n);
int					ft_isdigit(int c);
void				get_forks(t_philo *philo);
void				philo_eating(t_philo *philo);
void				philo_sleeping(t_philo *philo);
void				philo_thinking(t_philo *philo);
long				get_time(void);
int					ft_mutexes_init(t_dtls *dtls);
int					ft_philos_init(t_dtls *dtls);
int					ft_init(t_dtls *dtls, int ac, char **av);
#endif