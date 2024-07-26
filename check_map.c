/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:11:00 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/26 18:14:39 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_size(char **map)
{
	int	width;
	int	height;
	int	i;

	if (!map || !*map)
		return (0);
	width = ft_strlen(map[0]);
	if (width > MAX_WIDTH)
		return (0);
	height = 0;
	while (map[height])
		height++;
	if (height > MAX_HEIGHT)
		return (0);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != width) 
			return (0);
		i++;
	}
	return (1);
}
static int	count_char_in_map(char **map, char c)
{
	int		count;
	char	*ptr;

	count = 0;
	while (*map)
	{
		ptr = *map;
		ptr = ft_strchr(ptr, c);
		while (ptr)
		{
			count++;
			ptr = ft_strchr(ptr + 1, c);
		}
		map++;
	}
	return (count);
}
int	check_map_content(char **map)
{
	int	exit_c;
	int	collectible_c;
	int	start_position_c;

	exit_c = count_char_in_map(map, 'E');
	collectible_c = count_char_in_map(map, 'C');
	start_position_c = count_char_in_map(map, 'P');
	return (exit_c == 1 && start_position_c == 1 && collectible_c >= 1);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i]) 
	{
		j = 0;
		while (map[i][j])
		{
			if (((i == 0 || !map[i + 1]) && map[i][j] != '1') || ((j == 0 || !map[i][j + 1]) && map[i][j] != '1'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

