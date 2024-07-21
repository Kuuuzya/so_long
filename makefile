# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuznets <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 15:51:49 by skuznets          #+#    #+#              #
#    Updated: 2024/07/21 16:50:37 by skuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
AR = ar rc
SRCS = so_long.c ft_printf.c ft_printf_utils.c check_utils.c
CC = cc
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRCS:.c=.o)
RM = rm -rf

$(NAME):	$(OBJS)
	$(AR) $(NAME) $(OBJS)

all:	$(NAME)

clean:
			$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re