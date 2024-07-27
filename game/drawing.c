/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:25:16 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 11:01:25 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

static void	format_moves(char *buffer, int moves)
{
	char	*move_str;

	move_str = ft_itoa(moves);
	ft_strcpy(buffer, "Moves: ");
	ft_strcpy(buffer + ft_strlen("Moves: "), move_str);
	free(move_str);
}

static void	draw_tile(t_data *data, int x, int y)
{
	void	*img;

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
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	char	move_str[50];

	y = 0;
	while (y < data->height / TILE_SIZE)
	{
		x = 0;
		while (x < data->width / TILE_SIZE)
		{
			draw_tile(data, x, y);
			x++;
		}
		y++;
	}
	format_moves(move_str, data->moves);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, move_str);
}
