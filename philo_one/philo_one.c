/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:03:03 by elahyani          #+#    #+#             */
/*   Updated: 2021/02/01 11:07:45 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>


void	*myturn(void *arg)
{
	int		*iptr;

	iptr = (int *)malloc(sizeof(int));
	*iptr = 5;
	for (int i = 0 ; i < 8 ; i++)
	{
		sleep(1);
		printf("My Turn! %d %d\n", i, *iptr);
		(*iptr)++;
	}
	return (iptr);
}

void	*yourturn()
{
	for (int i = 0; i < 3 ; i++)
	{
		sleep(2);
		printf("Your Turn! %d\n", i);
	}
	return (NULL);
}

int		main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	int			*res;

	pthread_create(&t1, NULL, myturn, NULL);
	yourturn();
	pthread_join(t1, (void *)&res);
	printf("thread's done: *res=%d\n", *res);
	return (0);
}