# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 08:54:19 by elahyani          #+#    #+#              #
#    Updated: 2021/02/01 09:13:35 by elahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one.a

SRCS = philo_one.c

OBJ = $(SRCS:.c=.o)

LINKERFLAG = -Wall -Wextra -Werror -lpthread -c

MAIN = philo_one.c

all: $(NAME)

$(NAME):	$(OBJ)
			@ar rcs $(NAME) $(OBJ)
			@gcc $(MAIN) $(NAME) -o philo_one
			@echo Done!

%.o: %.c
		@gcc $(LINKERFLAG) $< -o $@

clean:
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)
		@rm -f philo_one

re: fclean all