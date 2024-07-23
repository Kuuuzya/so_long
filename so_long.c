/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:35:13 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/24 01:19:07 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strcmp(extension, ".ber") != 0)
	{
		ft_printf("%s", "Error: Invalid file extension\n");
		exit(1);
	}
}

char	**copy_old_lines(char **map, size_t size)
{
	char	**new_map;
	size_t	i;

	new_map = malloc((size + 2) * sizeof(char *));
	if (!new_map)
	{
		perror("Error: Failed to allocate memory");
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
	char		**map;
	char		*line;
	size_t		len;
	size_t		i;

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
	size_t	i;

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
		ft_printf("%s", "Error: Wrong number of arguments\n");
		exit(1);
	}
	check_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s", "Error: Failed to open file\n");
		exit(1);
	}
	map = read_file_into_array(fd);
	close(fd);
	if (check_map(map) == 1)
		{
		print_map(map);
		game_start(map);
		}
	else
		ft_printf("%s", "Error: Invalid map. Fix it!\n");
	return (0);
}
