/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:31:49 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 02:42:43 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_textures(t_data *data)
{
	int	img_width;
	int	img_height;

	img_width = TILE_SIZE;
	img_height = TILE_SIZE;
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "./assets/wall.xpm", &img_width, &img_height);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "./assets/floor.xpm", &img_width, &img_height);
	data->player_img[0] = mlx_xpm_file_to_image(data->mlx, "./assets/player1.xpm", &img_width, &img_height);
	data->player_img[1] = mlx_xpm_file_to_image(data->mlx, "./assets/player2.xpm", &img_width, &img_height);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "./assets/exit.xpm", &img_width, &img_height);
	data->collectible_img = mlx_xpm_file_to_image(data->mlx, "./assets/collectible.xpm", &img_width, &img_height);
	data->enemy_img = mlx_xpm_file_to_image(data->mlx, "./assets/enemy.xpm", &img_width, &img_height);
	if (!data->enemy_img || !data->floor_img || !data->wall_img || !data->player_img[0] || 
		!data->player_img[1] || !data->exit_img || !data->collectible_img)
	{
		ft_printf("Error loading one of texture\n");
		return (0);
	}
	return (1);
}

void	draw_map(t_data *data)
{
	int x;
	int y;
	void *img;
	char move_str[50];

	y = 0;
	while (y < data->height / TILE_SIZE)
	{
		x = 0;
		while (x < data->width / TILE_SIZE)
		{
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
			mlx_put_image_to_window(data->mlx, data->win, img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	sprintf(move_str, "Moves: %d", data->moves);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, move_str);
}

int	find_player(t_data *data, int *x, int *y)
{
	int i;
	int j;

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
	int i;
	int j;

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

void	end_game(t_data *data, const char *message)
{
	ft_printf("%s\n", message);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

void	animate_player(t_data *data)
{
	data->player_frame = (data->player_frame + 1) % 2;
}

void	move_player(t_data *data, int new_x, int new_y)
{
	int x;
	int y;

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
		ft_printf("Number of moves: %d\n", data->moves);
		animate_player(data);
	}
	else if (data->map[new_y][new_x] == 'E' && check_win(data))
	{
		end_game(data, "Вы выиграли!");
	}
}

void	move_enemy_towards_player(t_data *data, int ex, int ey, int px, int py)
{
	int new_x = ex;
	int new_y = ey;

	if (abs(px - ex) > abs(py - ey))
	{
		if (px > ex)
			new_x++;
		else if (px < ex)
			new_x--;
	}
	else
	{
		if (py > ey)
			new_y++;
		else if (py < ey)
			new_y--;
	}

	if (new_x >= 0 && new_x < data->width / TILE_SIZE &&
		new_y >= 0 && new_y < data->height / TILE_SIZE &&
		(data->map[new_y][new_x] == '0' || data->map[new_y][new_x] == 'P'))
	{
		if (data->map[new_y][new_x] == 'P')
			end_game(data, "Вы проиграли");
		data->map[ey][ex] = '0';
		data->map[new_y][new_x] = 'X';
	}
}

void	move_enemies(t_data *data)
{
	int x;
	int y;
	int px;
	int py;

	find_player(data, &px, &py);

	y = 0;
	while (y < data->height / TILE_SIZE)
	{
		x = 0;
		while (x < data->width / TILE_SIZE)
		{
			if (data->map[y][x] == 'X')
			{
				move_enemy_towards_player(data, x, y, px, py);
			}
			x++;
		}
		y++;
	}
	draw_map(data); // Обновляем карту после движения врагов
}

int	key_hook(int keycode, t_data *data)
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

int	close_game(t_data *data)
{
	end_game(data, "Игра закончена!");
	return (0);
}

int	game_loop(t_data *data)
{
	static int animation_counter = 0;

	if (animation_counter++ >= 100)
	{
		animate_player(data);
		animation_counter = 0;
	}

	draw_map(data);
	usleep(50000);
	return (0);
}

void	game_start(char **map)
{
	t_data data;

	get_map_size(map, &data.width, &data.height);
	data.height *= TILE_SIZE;
	data.width *= TILE_SIZE;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "The Elon Game");
	if (load_textures(&data) == 0)
		end_game(&data, "Ошибка загрузки текстур");
	data.map = map;
	data.moves = 0;
	data.player_frame = 0;
	draw_map(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}

