/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:35:13 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 02:21:10 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strcmp(extension, ".ber") != 0)
	{
		ft_printf("%s", "Error\nInvalid file extension\n");
		exit(1);
	}
}

char	**copy_old_lines(char **map, int size)
{
	char	**new_map;
	int	i;

	new_map = malloc((size + 2) * sizeof(char *));
	if (!new_map)
	{
		perror("Error\nFailed to allocate memory");
		exit(1);
	}
	i = 0;
	while (i < size)
	{
		new_map[i] = map[i];
		i++;
	}
	if (map)
		free(map);
	return (new_map);
}

char	**read_file_into_array(int fd)
{
	char	**map;
	char	*line;
	int		len;
	int		i;

	map = NULL;
	i = 0;
	while ((line = get_next_line(fd)) != NULL && *line != '\0')
	{
		map = copy_old_lines(map, i);
		map[i] = line;
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
	if (map)
		map[i] = NULL;
	return (map);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		write(1, map[i], ft_strlen(map[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	char	**map;

	if (argc != 2)
	{
		ft_printf("%s", "Error\nWrong number of arguments. Use ./so_long map_name.ber\n");
		exit(1);
	}
	check_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s", "Error\nFailed to open file\n");
		exit(1);
	}
	map = read_file_into_array(fd);
	close(fd);
	if (check_map(map) == 1)
		{
		ft_printf("%s", "Map is OK\n");
		game_start(map);
		}
	return (0);
}
