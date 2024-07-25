/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:59:53 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 19:16:37 by skuznets         ###   ########.fr       */
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

#define BUFFER_SIZE 42
#define MAX_WIDTH 32
#define MAX_HEIGHT 16
#define TILE_SIZE 64
#define ENEMY_SPEED 500000
#define ANIMATION_SPEED 200000
#define DEBUG 0

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
	int		game_over;
	int		enemies_updated;
} t_data;

typedef struct	s_flood_fill
{
	int	*visited;
	int	width;
	int	height;
	int	*reachable_c;
	int	*reachable_e;
}	t_flood_fill;

void	check_file(int	fd);
int		check_map(char	**map);
int		check_map_content(char	**map);
int		check_map_size(char **map);
int		check_walls(char **map);
int		check_path_availability(char	**map, int	result);
void	free_map(char **map);
void	game_start(t_data *data);

//libft functions and ft_printf
int		ft_printf(const char *format, ...);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
int		ft_strlen(const char *s);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_printnumber(int n);
int		ft_strcpy(char *dst, const char *src);
//check path utils
int		*init_visited(int width, int height);
void	count_items(char **map, int *total_c, int *total_e);
void	find_starting_point(char **map, int *x, int *y);
void	flood_fill(char **map, int x, int y, t_flood_fill *ff);
void	get_map_size(char **map, int *width, int *height);
//get next line utils
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
#endif