/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_and_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:39:27 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 12:14:32 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	free_sources(t_data *data)
{
	if (data->wall_img)
		mlx_destroy_image(data->mlx, data->wall_img);
	if (data->floor_img)
		mlx_destroy_image(data->mlx, data->floor_img);
	if (data->player_img[0])
		mlx_destroy_image(data->mlx, data->player_img[0]);
	if (data->player_img[1])
		mlx_destroy_image(data->mlx, data->player_img[1]);
	if (data->exit_img)
		mlx_destroy_image(data->mlx, data->exit_img);
	if (data->collectible_img)
		mlx_destroy_image(data->mlx, data->collectible_img);
	if (data->enemy_img)
		mlx_destroy_image(data->mlx, data->enemy_img);
	if (data->map)
		free_map(data->map);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
}

void	end_game(t_data *data, const char *message)
{
	ft_putstr(message);
	ft_putstr("\n");
	free_sources(data);
	//system("leaks so_long");
	exit(0);
}

int	load_textures(t_data *data)
{
	int	img_width;
	int	img_height;

	img_width = TILE_SIZE;
	img_height = TILE_SIZE;
	data->wall_img = mlx_xpm_file_to_image(data->mlx, \
"./assets/wall.xpm", &img_width, &img_height);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, \
"./assets/floor.xpm", &img_width, &img_height);
	data->player_img[0] = mlx_xpm_file_to_image(data->mlx, \
"./assets/player1.xpm", &img_width, &img_height);
	data->player_img[1] = mlx_xpm_file_to_image(data->mlx, \
"./assets/player2.xpm", &img_width, &img_height);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, \
"./assets/exit.xpm", &img_width, &img_height);
	data->collectible_img = mlx_xpm_file_to_image(data->mlx, \
"./assets/collectible.xpm", &img_width, &img_height);
	data->enemy_img = mlx_xpm_file_to_image(data->mlx, \
"./assets/enemy.xpm", &img_width, &img_height);
	if (!data->wall_img || !data->floor_img || !data->player_img[0] || \
!data->player_img[1] || !data->exit_img || !data->collectible_img || \
!data->enemy_img)
		return (0);
	return (1);
}

int	close_game(t_data *data)
{
	end_game(data, "Game was closed.");
	return (0);
}
