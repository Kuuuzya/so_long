/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:38:52 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 13:51:23 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strcmp(extension, ".ber") != 0)
	{
		ft_putstr("Error\nInvalid file extension\n");
		exit (1);
	}
}

static char	**resize_and_add_line(char **map, int count, char *line)
{
	char	**temp_map;
	size_t	len;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	temp_map = resize_map(map, count + 1);
	if (!temp_map)
	{
		free(line);
		free_map(map);
		return (NULL);
	}
	map = temp_map;
	map[count] = line;
	return (map);
}

static char	**read_file_into_array(int fd, int *size)
{
	char	**map;
	char	*line;
	int		count;

	map = NULL;
	count = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map = resize_and_add_line(map, count, line);
		if (!map)
		{
			free(line);
			return (NULL);
		}
		count++;
		line = get_next_line(fd);
	}
	if (map != NULL)
		map[count] = NULL;
	*size = count;
	return (map);
}

static int	process_arguments(int argc, char **argv, int *fd)
{
	if (argc != 2)
	{
		ft_putstr("Error\nWrong number of arguments. \
Use ./so_long map_name.ber\n");
		return (1);
	}
	check_extension(argv[1]);
	*fd = open(argv[1], O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr("Error\nFailed to open file\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		size;
	int		fd;
	t_data	data;

	if (process_arguments(argc, argv, &fd) != 0)
		return (1);
	data.map = read_file_into_array(fd, &size);
	close(fd);
	if (!data.map)
	{
		ft_putstr("Error\nFailed to read file\n");
		return (1);
	}
	if (check_map(data.map) == 1)
		game_start(&data);
	else
		free_map(data.map);
	return (0);
}
