/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:53:11 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/23 17:55:59 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void get_map_size(char **map, int *mapHeight, int *mapWidth) {
	*mapHeight = 0;
	*mapWidth = 0;
	while (map[*mapHeight] != NULL) {
		(*mapHeight)++;
	}
	if (*mapHeight > 0) {
		*mapWidth = ft_strlen(map[0]);
	}
}

void floodFill(char **map, int x, int y, int mapHeight, int mapWidth) {
	if (x < 0 || x >= mapHeight || y < 0 || y >= mapWidth || map[x][y] != '0') {
		return;
	}
	map[x][y] = 'F'; // Помечаем посещенную ячейку

	floodFill(map, x + 1, y, mapHeight, mapWidth); // вниз
	floodFill(map, x - 1, y, mapHeight, mapWidth); // вверх
	floodFill(map, x, y + 1, mapHeight, mapWidth); // вправо
	floodFill(map, x, y - 1, mapHeight, mapWidth); // влево
}

int find_start_point(char **map, int mapHeight, int mapWidth, int *startX, int *startY) {
	*startX = -1;
	*startY = -1;
	int i = 0;
	while (i < mapHeight) {
		int j = 0;
		while (j < mapWidth) {
			if (map[i][j] == 'P') {
				*startX = i;
				*startY = j;
				return 1; // Найдено
			}
			j++;
		}
		i++;
	}
	return 0; // Не найдено
}

int check_path_availability(char **map) {
	int mapHeight, mapWidth;
	int startX, startY;

	get_map_size(map, &mapHeight, &mapWidth);
	if (!find_start_point(map, mapHeight, mapWidth, &startX, &startY)) {
		printf("Ошибка: Начальная точка 'P' не найдена.\n");
		return -1;
	}

	floodFill(map, startX, startY, mapHeight, mapWidth);

	// Проверяем, достижимы ли 'C' и 'E' после применения floodFill
	int i = 0;
	int isPathAvailable = 0;
	while (i < mapHeight && !isPathAvailable) {
		int j = 0;
		while (j < mapWidth) {
			if ((map[i][j] == 'C' || map[i][j] == 'E') && map[i][j] == 'F') {
				isPathAvailable = 1;
				break;
			}
			j++;
		}
		i++;
	}

	if (isPathAvailable) {
		printf("Путь найден.\n");
		return (1);
	} else {
		printf("Путь не найден.\n");
		return (0);
	}
}

