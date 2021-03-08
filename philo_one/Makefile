# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kycho <kycho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/08 17:39:09 by kycho             #+#    #+#              #
#    Updated: 2021/03/08 17:48:08 by kycho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRCS = main.c
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
