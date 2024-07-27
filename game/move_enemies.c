/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:59:59 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 10:46:32 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_enemy_positions(int **enemy_positions, int enemy_count)
{
	int	i;

	i = 0;
	while (i < enemy_count)
	{
		free(enemy_positions[i]);
		i++;
	}
	free(enemy_positions);
}

int	add_enemy_position(int **enemy_positions, int enemy_count, int x, int y)
{
	enemy_positions[enemy_count] = (int *)malloc(2 * sizeof(int));
	if (!enemy_positions[enemy_count])
	{
		free_enemy_positions(enemy_positions, enemy_count);
		return (-1);
	}
	enemy_positions[enemy_count][0] = x;
	enemy_positions[enemy_count][1] = y;
	return (enemy_count + 1);
}

int	fill_enemy_positions(t_data *data, int **enemy_positions)
{
	int	x;
	int	y;
	int	enemy_count;

	enemy_count = 0;
	y = 0;
	while (y < data->height / TILE_SIZE)
	{
		x = 0;
		while (x < data->width / TILE_SIZE)
		{
			if (data->map[y][x] == 'X')
			{
				enemy_count = add_enemy_position(enemy_positions, \
				enemy_count, x, y);
				if (enemy_count == -1)
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (enemy_count);
}

void	move_all_enemies(t_data *data, int **enemy_positions, int enemy_count)
{
	int	i;
	int	ex;
	int	ey;

	i = 0;
	while (i < enemy_count)
	{
		ex = enemy_positions[i][0];
		ey = enemy_positions[i][1];
		move_enemy_random(data, ex, ey);
		i++;
	}
}

void	move_enemies(t_data *data)
{
	int	**enemy_positions;
	int	enemy_count;

	enemy_positions = (int **)malloc(data->height * \
	data->width * sizeof(int *));
	if (!enemy_positions)
		return ;
	enemy_count = fill_enemy_positions(data, enemy_positions);
	if (enemy_count == -1)
		return ;
	move_all_enemies(data, enemy_positions, enemy_count);
	free_enemy_positions(enemy_positions, enemy_count);
}
