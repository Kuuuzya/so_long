/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:34 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 09:57:28 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_flood_fill	init_flood_fill(int width, int height)
{
	t_flood_fill	ff;

	ff.visited = init_visited(width, height);
	ff.width = width;
	ff.height = height;
	ff.reachable_c = (int *)malloc(sizeof(int));
	ff.reachable_e = (int *)malloc(sizeof(int));
	if (ff.reachable_c)
		*ff.reachable_c = 0;
	if (ff.reachable_e)
		*ff.reachable_e = 0;
	ff.initial_c_count = 0;
	ff.initial_e_count = 0;
	return (ff);
}

void	free_resources(int *x, int *y, t_flood_fill *ff)
{
	free(ff->visited);
	free(ff->reachable_c);
	free(ff->reachable_e);
	free(x);
	free(y);
}

int	initialize_and_check_start_point(char **map, int **x, int **y)
{
	int	width;
	int	height;

	get_map_size(map, &width, &height);
	*x = (int *)malloc(sizeof(int));
	*y = (int *)malloc(sizeof(int));
	if (!(*x) || !(*y))
		return (0);
	find_starting_point(map, *x, *y);
	if (**x == -1 || **y == -1)
	{
		free(*x);
		free(*y);
		return (0);
	}
	return (1);
}

int	check_path_availability(char **map, int result)
{
	int				*x;
	int				*y;
	int				width;
	int				height;
	t_flood_fill	ff;

	if (!initialize_and_check_start_point(map, &x, &y))
		return (0);
	get_map_size(map, &width, &height);
	ff = init_flood_fill(width, height);
	if (!ff.visited || !ff.reachable_c || !ff.reachable_e)
	{
		free_resources(x, y, &ff);
		return (0);
	}
	count_items(map, &ff.initial_c_count, &ff.initial_e_count);
	flood_fill(map, *x, *y, &ff);
	result = (*ff.reachable_c == ff.initial_c_count && \
	*ff.reachable_e == ff.initial_e_count);
	free_resources(x, y, &ff);
	return (result);
}
