/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:38:43 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 13:38:47 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

char	**allocate_new_map(int new_size)
{
	char	**new_map;

	new_map = malloc((new_size + 1) * sizeof(char *));
	if (!new_map)
		perror("Error allocating new map");
	return (new_map);
}

char	**copy_map(char **new_map, char **map, int new_size)
{
	int	i;

	i = 0;
	while (map && map[i] && i < new_size)
	{
		new_map[i] = strdup(map[i]);
		if (!new_map[i])
		{
			perror("Error copying map string");
			free_map(new_map);
			return (NULL);
		}
		i++;
	}
	while (i <= new_size)
	{
		new_map[i] = NULL;
		i++;
	}
	return (new_map);
}

char	**resize_map(char **map, int new_size)
{
	char	**new_map;

	new_map = allocate_new_map(new_size);
	if (!new_map)
	{
		free_map(map);
		return (NULL);
	}
	new_map = copy_map(new_map, map, new_size);
	if (!new_map)
	{
		free_map(new_map);
		free_map(map);
		return (NULL);
	}
	free_map(map);
	return (new_map);
}
