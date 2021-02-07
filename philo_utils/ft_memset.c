/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:04:13 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/07 11:42:42 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one/philo_one.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	int		i;
	char	x;

	x = (unsigned char)c;
	str = (char *)b;
	i = 0;
	while (len)
	{
		str[i] = x;
		len--;
		i++;
	}
	return (str);
}
