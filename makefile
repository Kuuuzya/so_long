# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuznets <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 15:51:49 by skuznets          #+#    #+#              #
#    Updated: 2024/07/21 18:38:18 by skuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = so_long.c ft_printf.c ft_utils.c get_next_line.c get_next_line_utils.c check_map.c
CC = cc
FLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
RM = rm -rf

$(NAME):	
	$(CC) $(FLAGS) -o $(NAME) $(SRCS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re