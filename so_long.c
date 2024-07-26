/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:21:33 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/26 18:34:02 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

static void	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strcmp(extension, ".ber") != 0)
	{
		ft_putstr("Error\nInvalid file extension\n");
		// system("leaks so_long");
		exit(1);
	}
}


char **resize_map(char **map, int new_size) {
	char **new_map = realloc(map, (new_size + 1) * sizeof(char *));
	if (!new_map) {
		perror("Error reallocating map");
		free_map(map); 
		// system("leaks so_long");
		exit(1);
	}
	return new_map;
}

char **read_file_into_array(int fd, int *size) {
	char **map = NULL;
	char *line;
	int count = 0;

	map = resize_map(map, 0);  // Initialize map
	while ((line = get_next_line(fd)) != NULL) {
		// Trim the newline character
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n') {
			line[len - 1] = '\0';
		}
		map = resize_map(map, count + 1);
		map[count++] = line;  // Assign line to map
	}
	map[count] = NULL;  // Null-terminate the array
	*size = count;
	return map;
}


void print_map(char **map) {
	int i = 0;
	while (map[i] != NULL) {
		write(1, map[i], ft_strlen(map[i]));
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv) {
	int fd;
	int map_size;
	t_data data;

	if (argc != 2) {
		ft_putstr("Error\nWrong number of arguments. Use ./so_long map_name.ber\n");
		// system("leaks so_long");
		exit(1);
	}
	check_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		ft_putstr("Error\nFailed to open file\n");
		// system("leaks so_long");
		exit(1);
	}
	data.map = read_file_into_array(fd, &map_size);
	close(fd);
	//print_map(data.map);
	if (check_map(data.map) == 1) {
		ft_putstr("Map is OK\n");
		ft_putstr("Game is starting...\n");
		//print_map(data.map);
		game_start(&data); // Передача структуры данных в game_start
	} else 
		ft_putstr("Error\nInvalid map\n");
	system("leaks so_long");
	return (0);
}