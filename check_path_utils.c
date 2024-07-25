/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:40:13 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 14:04:53 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map_size(char **map, int *width, int *height)
{
	*height = 0;
	while (map[*height])
		(*height)++;
	*width = 0;
	while (map[0][*width])
		(*width)++;
}

void	flood_fill(char **map, int x, int y, t_flood_fill *ff)
{
	if (x < 0 || x >= ff->width || y < 0 || y >= ff->height
		|| ff->visited[y * ff->width + x] || map[y][x] == '1' ||
map[y][x] == 'X')
		return ;
	ff->visited[y * ff->width + x] = 1;
	if (map[y][x] == 'C')
		(*ff->reachable_c)++;
	if (map[y][x] == 'E')
		(*ff->reachable_e)++;
	flood_fill(map, x + 1, y, ff);
	flood_fill(map, x - 1, y, ff);
	flood_fill(map, x, y + 1, ff);
	flood_fill(map, x, y - 1, ff);
}

void	find_starting_point(char **map, int *x, int *y)
{
	int	i;
	int	width;
	int	height;

	get_map_size(map, &width, &height);
	*x = -1;
	*y = -1;
	i = 0;
	while (i < width * height)
	{
		if (map[i / width][i % width] == 'P')
		{
			*x = i % width;
			*y = i / width;
			break ;
		}
		i++;
	}
}

void	count_items(char **map, int *total_c, int *total_e)
{
	int	i;
	int	width;
	int	height;

	get_map_size(map, &width, &height);
	*total_c = 0;
	*total_e = 0;
	i = 0;
	while (i < width * height)
	{
		if (map[i / width][i % width] == 'C')
			(*total_c)++;
		if (map[i / width][i % width] == 'E')
			(*total_e)++;
		i++;
	}
}

int	*init_visited(int width, int height)
{
	int	*visited;
	int	i;

	visited = (int *)malloc(width * height * sizeof(int));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < width * height)
	{
		visited[i] = 0;
		i++;
	}
	return (visited);
}
