/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:19:03 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 13:42:08 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

void	animate_player(t_data *data)
{
	data->player_frame = (data->player_frame + 1) % 2;
}

void	print_moves(t_data *data)
{
	char	*str;

	ft_putstr("Moves: ");
	str = ft_itoa(data->moves);
	ft_putstr(str);
	free(str);
	ft_putstr("\n");
}

void	move_player(t_data *data, int new_x, int new_y)
{
	int		x;
	int		y;

	find_player(data, &x, &y);
	if (data->map[new_y][new_x] != '1' && data->map[new_y][new_x] != 'E')
	{
		if (data->map[new_y][new_x] == 'C')
			data->map[new_y][new_x] = '0';
		else if (data->map[new_y][new_x] == 'X')
			end_game(data, "You loose!");
		data->map[y][x] = '0';
		data->map[new_y][new_x] = 'P';
		data->moves++;
		animate_player(data);
		print_moves(data);
	}
	else if (data->map[new_y][new_x] == 'E' && check_win(data))
	{
		data->moves++;
		print_moves(data);
		end_game(data, "You win!");
	}
}
