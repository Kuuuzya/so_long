/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:53:11 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/24 01:33:00 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map_size(char **map, int *width, int *height)
{
	*height = 0;
	while (map[*height])
		(*height)++;
	*width = 0;
	while (map[0][*width])
		(*width)++;
}

void flood_fill(char **map, int x, int y, int *visited, int width, int height, int *reachable_c, int *reachable_e) {
    if (x < 0 || x >= width || y < 0 || y >= height || visited[y * width + x] || map[y][x] == '1')
        return;
    visited[y * width + x] = 1;
    if (map[y][x] == 'C')
        (*reachable_c)++;
    if (map[y][x] == 'E')
        (*reachable_e)++;
    flood_fill(map, x + 1, y, visited, width, height, reachable_c, reachable_e);
    flood_fill(map, x - 1, y, visited, width, height, reachable_c, reachable_e);
    flood_fill(map, x, y + 1, visited, width, height, reachable_c, reachable_e);
    flood_fill(map, x, y - 1, visited, width, height, reachable_c, reachable_e);
}

int check_path_availability(char **map) {
    int width, height;
    get_map_size(map, &width, &height);

    int *visited = (int *)malloc(width * height * sizeof(int));
    if (!visited)
        return 0;

    for (int i = 0; i < width * height; i++)
        visited[i] = 0;

    int x = -1, y = -1;
    for (int i = 0; i < width * height; i++) {
        if (map[i / width][i % width] == 'P') {
            x = i % width;
            y = i / width;
            break;
        }
    }

    if (x == -1 || y == -1) {
        free(visited);
        return 0;
    }

    int reachable_c = 0, reachable_e = 0;
    int total_c = 0, total_e = 0;

    for (int i = 0; i < width * height; i++) {
        if (map[i / width][i % width] == 'C')
            total_c++;
        if (map[i / width][i % width] == 'E')
            total_e++;
    }

    flood_fill(map, x, y, visited, width, height, &reachable_c, &reachable_e);

    free(visited);

    return (reachable_c == total_c && reachable_e == total_e);
}

