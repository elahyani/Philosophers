/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:27:01 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/17 11:57:25 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		args_checker(int ac, char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_atoi(av[1]) < 2 || ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60
	|| ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (1);
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_details	*details;

	details = malloc(sizeof(t_details));
	if (args_checker(ac, av))
		return (ft_error("error:\tbad arguments."));
	if (ft_init(details, ac, av))
		return (ft_error("error:\tinitialisation failed."));
	set_philos(details);
	clean_all(details);
	return (0);
}
