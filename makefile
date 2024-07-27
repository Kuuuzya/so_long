# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuznets <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 15:51:49 by skuznets          #+#    #+#              #
#    Updated: 2024/07/27 13:49:46 by skuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
SRCS = so_long.c gnl/get_next_line.c gnl/get_next_line_utils.c \
parsing/map.c parsing/check_map.c parsing/handle_errors.c parsing/check_path.c parsing/check_path_utils.c parsing/ft_utils.c \
game/random_movements.c game/load_and_end.c game/move_enemies.c game/move_player.c game/drawing.c game/game.c 
OBJS = $(SRCS:.c=.o)
NAME = so_long
MLX = -lm -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) ${MLX} $(CFLAGS) $(OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re