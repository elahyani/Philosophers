# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 08:54:19 by elahyani          #+#    #+#              #
#    Updated: 2021/02/17 11:49:25 by elahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRCS = philo_one.c ft_utils.c ft_init.c ft_clean.c philo_actions.c

LINKERFLAG = -Wall -Wextra -Werror

MAIN = main.c

all: $(NAME)

$(NAME):	$(SRCS) $(MAIN)
			@gcc $(MAIN) $(LINKERFLAG) $(SRCS) -o $(NAME)
			@echo Done!

clean:
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)
		@rm -f philo_one

re: fclean all