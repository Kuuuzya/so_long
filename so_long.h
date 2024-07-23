/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:59:53 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/24 02:35:28 by skuznets         ###   ########.fr       */
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
#define MAX_WIDTH 60
#define MAX_HEIGHT 33
#define TILE_SIZE 128
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800
#define MAX_TILE_SIZE 128

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_collectible;
	char	**map;
	int		width;
	int		height;
	int		tile_size;
}	t_data;

void	check_file(int fd);
int		check_map(char	**map);
void	get_map_size(char **map, int *width, int *height);
int		check_path_availability(char **map);
void	game_start(char **map);

//libft functions and ft_printf
int		ft_printf(const char *format, ...);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
//get next line utils
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
#endif