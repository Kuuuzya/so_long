/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   so_long.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: skuznets <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/26 18:21:33 by skuznets		  #+#	#+#			 */
/*   Updated: 2024/07/27 10:54:44 by skuznets		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "so_long.h"

// static void	check_extension(char *filename)
// {
// 	char	*extension;

// 	extension = ft_strrchr(filename, '.');
// 	if (!extension || ft_strcmp(extension, ".ber") != 0)
// 	{
// 		ft_putstr("Error\nInvalid file extension\n");
// 		system("leaks so_long");
// 		exit(1);
// 	}
// }

// char	**resize_and_add_line(char **map, int count, char *line)
// {
// 	char	**temp_map;
// 	size_t	len;

// 	len = strlen(line);
// 	if (len > 0 && line[len - 1] == '\n')
// 		line[len - 1] = '\0';
// 	temp_map = resize_map(map, count + 1);
// 	if (!temp_map)
// 	{
// 		free(line);
// 		free_map(map);
// 		return (NULL);
// 	}
// 	map = temp_map;
// 	map[count] = line;
// 	return (map);
// }

// char	**read_file_into_array(int fd, int *size)
// {
// 	char	**map;
// 	char	*line;
// 	int		count;

// 	line = NULL;
// 	map = NULL;
// 	count = 0;
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		map = resize_and_add_line(map, count, line);
// 		if (!map)
// 			return (NULL);
// 		count++;
// 		line = get_next_line(fd);
// 	}
// 	if (map != NULL)
// 		map[count] = NULL;
// 	*size = count;
// 	return (map);
// }

// int	tmain(int argc, char **argv)
// {
// 	int		fd;
// 	int		map_size;
// 	t_data	data;

// 	if (argc != 2)
// 	{
// 		ft_putstr("Error\nWrong number of arguments. \
// 		Use ./so_long map_name.ber\n");
// 		system("leaks so_long");
// 		exit(1);
// 	}
// //	check_extension(argv[1]);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_putstr("Error\nFailed to open file\n");
// 		system("leaks so_long");
// 		exit(1);
// 	}
// 	data.map = read_file_into_array(fd, &map_size);
// 	close(fd);
// 	// if (check_map(data.map) == 1)
// 	// {
// 	// 	ft_putstr("Map is OK!\nGame is starting...\n");
// 	// 	//game_start(&data);
// 	// }
// 	return (0);
// }

char **resize_and_add_line(char **map, int count, char *line)
{
    char **temp_map;
    size_t len;

    len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';

    temp_map = resize_map(map, count + 1);
    if (!temp_map)
    {
        free(line);
        free_map(map);
        return NULL;
    }
    map = temp_map;
    map[count] = line; // Добавляем строку в массив без освобождения
    return map;
}

char **read_file_into_array(int fd, int *size)
{
    char **map = NULL;
    char *line;
    int count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        map = resize_and_add_line(map, count, line);
        if (!map)
        {
            free(line); // Освобождаем строку в случае ошибки
            return NULL;
        }
        count++;
    }
    if (map != NULL)
    {
        map[count] = NULL;
    }
    *size = count;
    return map;
}

char *ft_read(int fd, char *buf, char *str)
{
    int r;
    char *temp;

    r = 1;
    while (!ft_strchr(str, '\n') && r != 0)
    {
        r = read(fd, buf, BUFFER_SIZE);
        if (r < 0)
        {
            free(str);
            return NULL;
        }
        buf[r] = '\0';
        if (!str)
        {
            str = ft_substr(buf, 0, r);
        }
        else
        {
            temp = ft_strjoin(str, buf);
            str = temp;
        }
    }
    return str;
}

char *ft_remain(char *str)
{
    char *rem;
    int i = 0;

    while (str[i] && str[i] != '\n')
        i++;
    i++;
    rem = ft_substr(str, i, ft_strlen(str) - i);
    free(str);
    return rem;
}

char *ft_line(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    i++;
    return ft_substr(str, 0, i);
}

char *get_next_line(int fd)
{
    char *current_line;
    char *buf = malloc(BUFFER_SIZE + 1);
    static char *str;

    if (BUFFER_SIZE < 1 || fd < 0 || !buf)
        return NULL;

    str = ft_read(fd, buf, str);
    free(buf);
    if (!str || str[0] == '\0')
    {
        free(str);
        str = NULL;
        return NULL;
    }
    current_line = ft_line(str);
    str = ft_remain(str);
    return current_line;
}

char *ft_strchr(const char *s, int c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return NULL;
}

char *concat_strings(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    if (!result)
        return NULL;
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *ft_strjoin(char *s1, char *s2)
{
    char *result;

    if (!s1)
    {
        s1 = malloc(1);
        if (!s1)
            return NULL;
        s1[0] = '\0';
    }
    if (!s2)
    {
        free(s1);
        return NULL;
    }
    result = concat_strings(s1, s2);
    free(s1);
    return result;
}

int ft_strlen(const char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

char *ft_substr(char *s, int start, int len)
{
    char *str;
    int i = 0, k = 0;

    if (!s)
        return NULL;
    if (ft_strlen(s) < len)
        len = ft_strlen(s);
    str = malloc(sizeof(*s) * (len + 1));
    if (!str)
        return NULL;
    while (s[i])
    {
        if (i >= start && k < len)
            str[k++] = s[i];
        i++;
    }
    str[k] = '\0';
    return str;
}

void free_map(char **map)
{
    int i = 0;
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

char **allocate_new_map(int new_size)
{
    char **new_map = malloc((new_size + 1) * sizeof(char *));
    if (!new_map)
        perror("Error allocating new map");
    return new_map;
}

char **copy_map(char **new_map, char **map, int new_size)
{
    int i = 0;
    while (map && map[i] && i < new_size)
    {
        new_map[i] = strdup(map[i]);
        if (!new_map[i])
        {
            perror("Error copying map string");
            free_map(new_map);
            return NULL;
        }
        i++;
    }
    while (i <= new_size)
    {
        new_map[i] = NULL;
        i++;
    }
    return new_map;
}

char **resize_map(char **map, int new_size)
{
    char **new_map = allocate_new_map(new_size);
    if (!new_map)
    {
        free_map(map);
        return NULL;
    }
    new_map = copy_map(new_map, map, new_size);
    if (!new_map)
    {
        free_map(map);
        return NULL;
    }
    free(map);
    return new_map;
}

int tmain(int argc, char **argv)
{
	t_data	data;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }
    int size;
    data.map = read_file_into_array(fd, &size);
	game_start(&data);
    close(fd);
    if (!data.map)
    {
        fprintf(stderr, "Error reading map\n");
        return 1;
    }
    // Здесь можно добавить код для обработки карты...
    free_map(data.map);
    return 0;
}

int	main(int argc, char **argv)
{
	tmain(argc, argv);
	//system("leaks so_long");
	return (0);
}