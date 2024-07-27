/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:59:53 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 12:15:34 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>
# include <sanitizer/asan_interface.h>

# define BUFFER_SIZE 1024
# define MAX_WIDTH 33
# define MAX_HEIGHT 16
# define TILE_SIZE 64

typedef struct s_data
{
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
}	t_data;

typedef struct s_flood_fill
{
	int	*visited;
	int	width;
	int	height;
	int	*reachable_c;
	int	*reachable_e;
	int	initial_c_count;
	int	initial_e_count;
}	t_flood_fill;

typedef struct s_valid_dirs
{
	int	directions[4][2];
	int	valid_directions[4][2];
	int	valid_count;
}	t_valid_dirs;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

void	check_file(int fd);
int		check_map(char **map);
int		check_map_content(char **map);
int		check_map_size(char **map);
int		check_walls(char **map);
int		check_path_availability(char	**map, int result);
void	free_map(char **map);
char	**resize_map(char **map, int new_size);
void	game_start(t_data *data);

//ft functions and get next line utils
void	ft_putstr(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
int		ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*ft_itoa(int n);
//check path utils
int		*init_visited(int width, int height);
void	count_items(char **map, int *total_c, int *total_e);
void	find_starting_point(char **map, int *x, int *y);
void	flood_fill(char **map, int x, int y, t_flood_fill *ff);
void	get_map_size(char **map, int *width, int *height);
//game
int		load_textures(t_data *data);
void	end_game(t_data *data, const char *message);
void	move_enemy_random(t_data *data, int ex, int ey);
void	move_enemies(t_data *data);
int		close_game(t_data *data);
void	draw_map(t_data *data);
void	move_player(t_data *data, int new_x, int new_y);
int		check_win(t_data *data);
void	animate_player(t_data *data);
int		find_player(t_data *data, int *x, int *y);
#endif