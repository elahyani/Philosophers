# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 16:06:27 by elahyani          #+#    #+#              #
#    Updated: 2021/02/20 16:06:43 by elahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

SRCS = philo_three.c ft_utils.c ft_init.c ft_clean.c philo_actions.c ft_itoa.c

LINKERFLAG = -Wall -Wextra -Werror

MAIN = main.c

all: $(NAME)

$(NAME): 	$(MAIN) $(SRCS)
			@gcc $(MAIN) $(LINKERFLAG) $(SRCS) -o $(NAME)
			@echo Done!

clean:
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)

re: fclean all