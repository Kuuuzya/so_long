/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:13 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/21 19:18:44 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map_size(char **map)
{
	size_t	width;
	size_t	i;

	if (!map || !*map)
		return (0);
	width = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != width)
			return (0);
		i++;
	}
	return (1);
}

static size_t	count_char_in_map(char **map, char c)
{
	size_t	count;
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

static int	check_map_content(char **map)
{
	size_t	exit_c;
	size_t	collectible_c;
	size_t	start_position_c;

	exit_c = count_char_in_map(map, 'E');
	collectible_c = count_char_in_map(map, 'C');
	start_position_c = count_char_in_map(map, 'P');
	return (exit_c == 1 && start_position_c == 1 && collectible_c >= 1);
}

int	check_walls(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || !map[i + 1]) && map[i][j] != '1')
				return (0);
			if ((j == 0 || !map[i][j + 1]) && map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(char	**map)
{
	if (check_map_size(map) == 0)
	{
		ft_printf("%s", "Error: The map is not rectangular\n");
		return (0);
	}
	else if (check_walls(map) == 0)
	{
		ft_printf("%s", "Error: The map is not surrounded by walls\n");
		return (0);
	}
	else if (check_map_content(map) == 0)
	{
		ft_printf("%s", "Error: The map must contain 1 exit, at least 1 collectible,\
and 1 starting position\n");
		return (0);
	}
	else
		return (1);
}
