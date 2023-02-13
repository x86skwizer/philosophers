# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 05:06:02 by yamrire           #+#    #+#              #
#    Updated: 2023/02/13 10:29:34 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./utils/ft_atoi.c ./utils/ft_strchr.c ./utils/ft_strlen.c main.c
NAME = philo
CC = cc
FLAGS = -pthread
OBJ = $(SRC:%.c=%.o)

all : $(NAME) $(OBJ)

$(NAME) :
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	
re : fclean all