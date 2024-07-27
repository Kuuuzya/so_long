/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:27:45 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 11:18:05 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_win(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height / TILE_SIZE)
	{
		j = 0;
		while (j < data->width / TILE_SIZE)
		{
			if (data->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	key_hook(int keycode, t_data *data)
{
	int	x;
	int	y;

	if (keycode == 53)
		end_game(data, "Game was exited.");
	else
	{
		find_player(data, &x, &y);
		if (keycode == 13 || keycode == 126)
			move_player(data, x, y - 1);
		else if (keycode == 0 || keycode == 123)
			move_player(data, x - 1, y);
		else if (keycode == 1 || keycode == 125)
			move_player(data, x, y + 1);
		else if (keycode == 2 || keycode == 124)
			move_player(data, x + 1, y);
		move_enemies(data);
	}
	draw_map(data);
	return (0);
}

int	game_loop(t_data *data)
{
	static int	player_animation_counter;

	player_animation_counter = 0;
	if (player_animation_counter++ >= 5)
	{
		animate_player(data);
		player_animation_counter = 0;
	}
	draw_map(data);
	return (0);
}

void	game_start(t_data *data)
{
	get_map_size(data->map, &data->width, &data->height);
	data->height *= TILE_SIZE;
	data->width *= TILE_SIZE;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, \
	data->width, data->height, "The Elon Game");
	if (load_textures(data) == 0)
		end_game(data, "Error loading textures");
	data->moves = 0;
	data->player_frame = 0;
	draw_map(data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}
