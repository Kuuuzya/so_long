/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:59:53 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 11:44:17 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>
#include <math.h>

#define BUFFER_SIZE 10
#define MAX_WIDTH 23
#define MAX_HEIGHT 15
#define TILE_SIZE 64
#define ENEMY_SPEED 500000
#define ANIMATION_SPEED 200000 

typedef struct s_data {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	char	**map;
	int		moves;
	void	*player_img[2]; 
	void	*enemy_img;
	void	*exit_img;
	void	*collectible_img;
	void	*wall_img;
	void	*floor_img;
	int		player_frame;
} t_data;

void	check_file(int fd);
int		check_map(char	**map);
void	get_map_size(char **map, int *width, int *height);
int		check_path_availability(char **map);
void	game_start(char **map);

//libft functions and ft_printf
int		ft_printf(const char *format, ...);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
int		ft_strlen(const char *s);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_printnumber(int n);
//get next line utils
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
#endif