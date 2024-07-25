/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:31:49 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 15:26:10 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int load_textures(t_data *data)
{
	int img_width;
	int img_height;

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

void draw_map(t_data *data)
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
	snprintf(move_str, sizeof(move_str), "Moves: %d", data->moves);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, move_str);
}

int find_player(t_data *data, int *x, int *y)
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

int check_win(t_data *data)
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

void end_game(t_data *data, const char *message)
{
	ft_printf("%s\n", message);
	// Освобождение ресурсов
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
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	system("leaks so_long");
	exit(0);
}

void animate_player(t_data *data)
{
	data->player_frame = (data->player_frame + 1) % 2;
}

void move_player(t_data *data, int new_x, int new_y)
{
	int x;
	int y;

	if (DEBUG)
		printf("Entering move_player\n");

	find_player(data, &x, &y);

	if (DEBUG)
	{
		printf("Player position: (%d, %d)\n", x, y);
		printf("New position: (%d, %d)\n", new_x, new_y);
	}

	if (data->map[new_y][new_x] != '1' && data->map[new_y][new_x] != 'E')
	{
		if (data->map[new_y][new_x] == 'C')
			data->map[new_y][new_x] = '0';
		else if (data->map[new_y][new_x] == 'X')
			end_game(data, "Вы проиграли");

		data->map[y][x] = '0';
		data->map[new_y][new_x] = 'P';
		data->moves++;

		if (DEBUG)
			printf("Number of moves: %d\n", data->moves);

		animate_player(data);
	}
	else if (data->map[new_y][new_x] == 'E' && check_win(data))
	{
		end_game(data, "Вы выиграли!");
	}

	if (DEBUG)
		printf("Exiting move_player\n");
}

void move_enemy_random(t_data *data, int ex, int ey)
{
	int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int valid_directions[4][2];
	int valid_count = 0;

	for (int i = 0; i < 4; i++)
	{
		int new_x = ex + directions[i][0];
		int new_y = ey + directions[i][1];

		if (new_x >= 0 && new_x < data->width / TILE_SIZE && new_y >= 0 && new_y < data->height / TILE_SIZE)
		{
			if (data->map[new_y][new_x] != '1' && data->map[new_y][new_x] != 'E' && data->map[new_y][new_x] != 'X' && data->map[new_y][new_x] != 'C')
			{
				valid_directions[valid_count][0] = new_x;
				valid_directions[valid_count][1] = new_y;
				valid_count++;
			}
		}
	}

	if (valid_count > 0)
	{
		int random_index = rand() % valid_count;
		int new_x = valid_directions[random_index][0];
		int new_y = valid_directions[random_index][1];

		if (data->map[new_y][new_x] == 'P')
			data->game_over = 1;  // Устанавливаем флаг game_over
		else
		{
			data->map[new_y][new_x] = 'X';
			data->map[ey][ex] = '0';
		}
	}
}

void move_enemies(t_data *data)
{
	int x, y;
	int **enemy_positions = NULL;
	int enemy_count = 0;

	if (DEBUG)
		printf("Entering move_enemies\n");

	// Динамическое выделение памяти для массива позиций врагов
	enemy_positions = (int **)malloc(data->height * data->width * sizeof(int *));
	if (!enemy_positions)
	{
		printf("Memory allocation failed for enemy_positions\n");
		return;
	}

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
					printf("Memory allocation failed for enemy_positions[%d]\n", enemy_count);
					// Освобождение уже выделенной памяти перед выходом
					for (int i = 0; i < enemy_count; i++)
					{
						free(enemy_positions[i]);
					}
					free(enemy_positions);
					return;
				}
				enemy_positions[enemy_count][0] = x;
				enemy_positions[enemy_count][1] = y;
				enemy_count++;
			}
		}
	}

	if (DEBUG)
		printf("Number of enemies: %d\n", enemy_count);

	for (int i = 0; i < enemy_count; i++)
	{
		int ex = enemy_positions[i][0];
		int ey = enemy_positions[i][1];
		move_enemy_random(data, ex, ey);
	}

	// Освобождение памяти после использования
	for (int i = 0; i < enemy_count; i++)
	{
		free(enemy_positions[i]);
	}
	free(enemy_positions);

	if (DEBUG)
		printf("Exiting move_enemies\n");
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

int game_loop(t_data *data)
{
	static int player_animation_counter = 0;

	if (player_animation_counter++ >= 10)
	{
		animate_player(data);
		player_animation_counter = 0;
	}

	draw_map(data);
	usleep(50000);
	return (0);
}

int close_game(t_data *data)
{
	end_game(data, "Игра закрыта");
	return (0);
}

void game_start(char **map)
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
	data.game_over = 0;  // Инициализация флага game_over
	data.enemies_updated = 1; // Инициализация флага обновления врагов
	draw_map(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
