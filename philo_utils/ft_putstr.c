/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:10:06 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/07 11:45:30 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one/philo_one.h"

void	ft_putstr(char *s)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			write (1, &s[i], 1);
			i++;
		}
	}
}