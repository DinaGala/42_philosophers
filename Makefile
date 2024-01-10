# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 17:30:59 by nzhuzhle          #+#    #+#              #
#    Updated: 2024/01/10 20:18:56 by nzhuzhle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = philo.h
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -pthread -I ./ #-g -fsanitize=thread

SRCS = philo.c routine.c time.c utils.c

OBJ = $(SRCS:.c=.o) 
DEPS = $(SRCS:.c=.d)
	
%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

-include $(DEPS)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(^) -o $(NAME)

clean:
	rm -f $(OBJ) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
