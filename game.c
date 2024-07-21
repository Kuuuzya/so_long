/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:31:49 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/21 20:46:54 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	load_textures(t_data *data)
{
	int img_width;
	int img_height;
	data->img_wall = mlx_xpm_file_to_image(data->mlx, "./assets/wall.xpm", &img_width, &img_height);
	data->img_floor = mlx_xpm_file_to_image(data->mlx, "./assets/floor.xpm", &img_width, &img_height);
//	data->img_player = mlx_xpm_file_to_image(data->mlx, "path_to_player.xpm", &data->width, &data->height);
//	data->img_exit = mlx_xpm_file_to_image(data->mlx, "path_to_exit.xpm", &data->width, &data->height);
//	data->img_collectible = mlx_xpm_file_to_image(data->mlx, "path_to_collectible.xpm", &data->width, &data->height);
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->img_wall, j * 32, i * 32);
			else if (data->map[i][j] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->img_floor, j * 32, i * 32);
			else if (data->map[i][j] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->img_player, j * 32, i * 32);
			else if (data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->img_exit, j * 32, i * 32);
			else if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->img_collectible, j * 32, i * 32);
			j++;
		}
		i++;
	}
}

void game_start(char **map)
{
	t_data	data;
	int map_width = ft_strlen(map[0]) * 32; // assuming all rows have the same length
	int map_height = 0;
	while (map[map_height])
		map_height++;
	map_height *= 32;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, map_width, map_height, "so_long");
	load_textures(&data);
	data.map = map;
	draw_map(&data);

	mlx_loop(data.mlx);
}