/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:27:45 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/26 18:33:21 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	void	*img;
	char	move_str[50];

	y = 0;
	while (y < data->height / TILE_SIZE)
	{
		x = 0;
		while (x < data->width / TILE_SIZE)
		{
			img = NULL;
			if (data->map[y][x] == '1')
				img = data->wall_img;
			else if (data->map[y][x] == '0')
				img = data->floor_img;
			else if (data->map[y][x] == 'P')
				img = data->player_img[data->player_frame];
			else if (data->map[y][x] == 'C')
				img = data->collectible_img;
			else if (data->map[y][x] == 'E')
				img = data->exit_img;
			else if (data->map[y][x] == 'X')
				img = data->enemy_img;
			if (img)
				mlx_put_image_to_window(data->mlx, data->win, \
img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	snprintf(move_str, sizeof(move_str), "Moves: %d", data->moves);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, move_str);
}

int	find_player(t_data *data, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height / TILE_SIZE)
	{
		j = 0;
		while (j < data->width / TILE_SIZE)
		{
			if (data->map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

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

void	animate_player(t_data *data)
{
	data->player_frame = (data->player_frame + 1) % 2;
}

void	move_player(t_data *data, int new_x, int new_y)
{
	int	x;
	int	y;

	find_player(data, &x, &y);
	if (data->map[new_y][new_x] != '1' && data->map[new_y][new_x] != 'E')
	{
		if (data->map[new_y][new_x] == 'C')
			data->map[new_y][new_x] = '0';
		else if (data->map[new_y][new_x] == 'X')
			end_game(data, "Вы проиграли");

		data->map[y][x] = '0';
		data->map[new_y][new_x] = 'P';
		data->moves++;
		animate_player(data);
	}
	else if (data->map[new_y][new_x] == 'E' && check_win(data))
	{
		end_game(data, "Вы выиграли!");
	}
}


void move_enemies(t_data *data)
{
	int x, y;
	int **enemy_positions = NULL;
	int enemy_count = 0;

	// Динамическое выделение памяти для массива позиций врагов
	enemy_positions = (int **)malloc(data->height * data->width * sizeof(int *));
	if (!enemy_positions)
		return;
	enemy_count = 0;
	for (y = 0; y < data->height / TILE_SIZE; y++)
	{
		for (x = 0; x < data->width / TILE_SIZE; x++)
		{
			if (data->map[y][x] == 'X')
			{
				enemy_positions[enemy_count] = (int *)malloc(2 * sizeof(int));
				if (!enemy_positions[enemy_count])
				{
					for (int i = 0; i < enemy_count; i++)
					{
						free(enemy_positions[i]);
					}
					free(enemy_positions);
					return ;
				}
				enemy_positions[enemy_count][0] = x;
				enemy_positions[enemy_count][1] = y;
				enemy_count++;
			}
		}
	}

	for (int i = 0; i < enemy_count; i++)
	{
		int ex = enemy_positions[i][0];
		int ey = enemy_positions[i][1];
		move_enemy_random(data, ex, ey);
	}
	for (int i = 0; i < enemy_count; i++)
		free(enemy_positions[i]);
	free(enemy_positions);
}

int key_hook(int keycode, t_data *data)
{
	int x;
	int y;

	if (keycode == 53)
		end_game(data, "Игра закончена!");
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

		move_enemies(data); // Двигаем врагов при каждом движении игрока
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

int	close_game(t_data *data)
{
	end_game(data, "Игра закрыта");
	return (0);
}

void game_start(t_data *data)
{
	get_map_size(data->map, &data->width, &data->height);
	data->height *= TILE_SIZE;
	data->width *= TILE_SIZE;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "The Elon Game");
	if (load_textures(data) == 0)
		end_game(data, "Ошибка загрузки текстур");
	data->moves = 0;
	data->player_frame = 0;
	draw_map(data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}
