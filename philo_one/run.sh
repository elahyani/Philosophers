#!/bin/bash

gcc -pthread ../philo_utils/ft_strlen.c ../philo_utils/ft_isdigit.c ../philo_utils/ft_atoi.c ../philo_utils/ft_putstr.c ../philo_utils/ft_putnbr.c philo_actions.c ft_init.c philo_one.c -o philo_one
