/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:51:05 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/19 16:54:38 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK_A		" has taken a fork"
# define DIE_A		" died"
# define EAT_A		" is eating"
# define SLEEP_A	" is sleeping"
# define THINK_A	" is thinking"

typedef struct			s_details
{
	int					nb_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					nb_must_eat;
	long				start_time;
	pthread_mutex_t		*mutex_forks;
	pthread_mutex_t		*mutex_die;
	pthread_mutex_t		*mutex_msg;
	struct s_philo		*philo;
}						t_details;

typedef struct			s_philo
{
	int					id;
	long				end;
	long				start;
	int					ph_is_eating;
	int					nb_must_eat;
	int					left_fork;
	int					right_fork;
	int					eat_cnt_reached;
	pthread_mutex_t		*philo_mutex;
	struct s_details	*details;
}						t_philo;

int						ft_atoi(const char *str);
int						ft_strlen(const char *s);
int						ft_isdigit(int c);
void					get_forks(t_philo *philo);
void					philo_eating(t_philo *philo);
void					philo_sleeping(t_philo *philo);
void					philo_thinking(t_philo *philo);
long					get_time(void);
int						ft_mutexes_init(t_details *details);
t_philo					*ft_philos_init(t_details *details);
int						ft_init(t_details *details, int ac, char **av);
void					clean_all(t_details *details);
int						ft_error(char	*err_msg);
void					set_philos(t_details *details);

#endif
