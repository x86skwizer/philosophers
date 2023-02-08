# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 05:06:02 by yamrire           #+#    #+#              #
#    Updated: 2023/02/03 04:40:02 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./utils/ft_atoi.c ./utils/ft_strchr.c ./utils/ft_strlen.c main.c
NAME = philo
CC = cc
FLAGS = -Wall -pthread -g
OBJ = $(SRC:%.c=%.o)

all : $(NAME) $(OBJ)

$(NAME) : $(OBJ)
	$(CC) $(FLAG) -c $< -o $@
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	
re : fclean all