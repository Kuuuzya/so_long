/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:57:22 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 11:39:59 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	handle_map_error(const char *message)
{
	ft_putstr(message);
	return (0);
}

int	check_map(char **map)
{
	if (map == NULL)
		return (handle_map_error("Error\nMap is NULL\n"));
	if (check_map_size(map) == 0)
		return (handle_map_error("Error\nThe map is not \
rectangular or too large (33 x 16 is max)\n"));
	if (check_walls(map) == 0)
		return (handle_map_error("Error\nThe map is not \
surrounded by walls\n"));
	if (check_map_content(map) == 0)
		return (handle_map_error("Error\nThe map must \
contain 1 exit, at least 1 collectible, and 1 starting position\n"));
	if (check_path_availability(map, 0) == 0)
		return (handle_map_error("Error\nThe map is not valid. No ways\n"));
	return (1);
}
