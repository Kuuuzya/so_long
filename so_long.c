/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:35:13 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 19:16:02 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"

void free_map(char **map) {
    if (!map) return;
    for (int i = 0; map[i] != NULL; i++) {
        free(map[i]);
    }
    free(map);
}

static void check_extension(char *filename) {
    char *extension = ft_strrchr(filename, '.');
    if (!extension || ft_strcmp(extension, ".ber") != 0) {
        printf("%s", "Error\nInvalid file extension\n");
        exit(1);
    }
}

char **copy_old_lines(char **map, int size) {
    char **new_map;
    int i;

    new_map = malloc((size + 1) * sizeof(char *));
    if (!new_map) {
        perror("Error\nFailed to allocate memory");
        if (map) free_map(map);
        exit(1);
    }
    for (i = 0; i < size; i++) {
        new_map[i] = malloc((ft_strlen(map[i]) + 1) * sizeof(char));
        if (!new_map[i]) {
            perror("Error\nFailed to allocate memory for new_map[i]");
            while (--i >= 0) free(new_map[i]);
            free(new_map);
            if (map) free_map(map);
            exit(1);
        }
        printf("copy_old_lines: copying map[%d] to new_map[%d] from address %p to %p\n", i, i, (void *)map[i], (void *)new_map[i]);
        ft_strcpy(new_map[i], map[i]);
    }
    new_map[size] = NULL;
    printf("copy_old_lines: completed copying, new_map[%d] is NULL\n", size);
    return new_map;
}

char **read_file_into_array(int fd, int *size) {
    char **map = NULL;
    char *line;
    int len;
    int i = 0;

    map = malloc(sizeof(char *));
    if (!map) {
        perror("Error\nFailed to allocate memory");
        exit(1);
    }
    map[0] = NULL;
    
    while ((line = get_next_line(fd)) != NULL) {
        if (*line != '\0') {
            printf("read_file_into_array: read line %d\n", i);
            char **temp = copy_old_lines(map, i);
            map = temp;
            map[i] = line;
            len = ft_strlen(map[i]);
            if (len > 0 && map[i][len - 1] == '\n') map[i][len - 1] = '\0';
            i++;
        } else {
            free(line);
        }
    }
    // Добавляем завершающий NULL
    map = realloc(map, (i + 1) * sizeof(char *));
    if (!map) {
        perror("Error\nFailed to allocate memory");
        exit(1);
    }
    map[i] = NULL;
    *size = i;
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
    char **map;
    int map_size;
    t_data data;

    if (argc != 2) {
        printf("%s", "Error\nWrong number of arguments. Use ./so_long map_name.ber\n");
        exit(1);
    }
    check_extension(argv[1]);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("%s", "Error\nFailed to open file\n");
        exit(1);
    }
    printf("start reading\n\n");
    map = read_file_into_array(fd, &map_size);
    close(fd);
    printf("start checking\n\n");
    if (check_map(map) == 1) {
        printf("%s", "Map is OK\n");
        print_map(map);
        data.map = map; // Инициализация карты в структуре данных
        game_start(&data); // Передача структуры данных в game_start
    } else {
        printf("%s", "Error\nInvalid map\n");
    }
    // Освобождение карты в случае неудачи
    if (map) 
        free_map(map); 
    return 0;
}