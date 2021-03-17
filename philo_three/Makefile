# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kycho <kycho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/08 17:39:09 by kycho             #+#    #+#              #
#    Updated: 2021/03/17 13:55:55 by kycho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

SRCS = main.c \
		init.c \
		execute.c \
		get_msg.c \
		check_simul_end.c \
		utils.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf 

.SUFFIXES: .c.o
.PHONY : all clean fclean re

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean :
	$(RM) $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
