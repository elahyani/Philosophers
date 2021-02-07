/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:21:44 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/07 11:49:09 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one/philo_one.h"

void	ft_putnbr(int n)
{
	long nb;
	char	nbc;
	char	nbc2;

	nbc = nb % 10 + '0';
	nbc2 = nb + '0';
	nb = n;
	if (nb < 0)
	{
		write (1, "-", 1);
		nb = nb * -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		write (1, &nbc, 1);
	}
	else
		write (1, &nbc2, 1);
}
