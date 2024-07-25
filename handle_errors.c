/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:38:12 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 14:10:34 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	handle_map_error(char **map, const char *message)
{
	ft_printf("%s", message);
	free_map(map);
	return (0);
}

int	check_map(char	**map)
{
	if (check_map_size(map) == 0)
		return (handle_map_error(map, "Error\nThe map is not rectangular\
 or too large (32 × 16 is max)\n"));
	if (check_walls(map) == 0)
		return (handle_map_error(map, "Error\nThe map is not surrounded\
 by walls\n"));
	if (check_map_content(map) == 0)
		return (handle_map_error(map, "Error\nThe map must contain 1 exit,\
 at least 1 collectible, and 1 starting position\n"));
	if (check_path_availability(map, 0) == 0)
		return (handle_map_error(map, "Error\nThe map is not valid.\
 No ways\n"));
	return (1);
}
