/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:13 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 16:30:34 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "so_long.h"
int check_map_size(char **map)
{
    int width;
    int height;
    int i;

    if (!map || !*map) {
        printf("check_map_size: map is NULL or empty\n");
        return 0;
    }
    width = ft_strlen(map[0]);
    printf("check_map_size: width of first row = %d\n", width);
    if (width > MAX_WIDTH) {
        printf("check_map_size: width %d is greater than MAX_WIDTH %d\n", width, MAX_WIDTH);
        return 0;
    }
    height = 0;
    while (map[height])
        height++;
    printf("check_map_size: height = %d\n", height);
    if (height > MAX_HEIGHT) {
        printf("check_map_size: height %d is greater than MAX_HEIGHT %d\n", height, MAX_HEIGHT);
        return 0;
    }
    i = 1;
    while (map[i]) {
        if (ft_strlen(map[i]) != width) {
            printf("check_map_size: line %d has different width\n", i);
            return 0;
        }
        i++;
    }
    return 1;
}
static int count_char_in_map(char **map, char c)
{
    int count;
    char *ptr;

    count = 0;
    while (*map) {
        ptr = *map;
        ptr = ft_strchr(ptr, c);
        while (ptr) {
            count++;
            ptr = ft_strchr(ptr + 1, c);
        }
        map++;
    }
    printf("count_char_in_map: character '%c' appears %d times\n", c, count);
    return count;
}
int check_map_content(char **map)
{
    int exit_c;
    int collectible_c;
    int start_position_c;

    exit_c = count_char_in_map(map, 'E');
    collectible_c = count_char_in_map(map, 'C');
    start_position_c = count_char_in_map(map, 'P');
    printf("check_map_content: exits = %d, collectibles = %d, start positions = %d\n", exit_c, collectible_c, start_position_c);
    return (exit_c == 1 && start_position_c == 1 && collectible_c >= 1);
}

int check_walls(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i]) {
        j = 0;
        while (map[i][j]) {
            if ((i == 0 || !map[i + 1]) && map[i][j] != '1') {
                printf("check_walls: error at edge i=%d, j=%d\n", i, j);
                return 0;
            }
            if ((j == 0 || !map[i][j + 1]) && map[i][j] != '1') {
                printf("check_walls: error at edge i=%d, j=%d\n", i, j);
                return 0;
            }
            j++;
        }
        i++;
    }
    return 1;
}

