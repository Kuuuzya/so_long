/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:38:12 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 16:33:27 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//void free_map(char **map)
//{
//    int i;

//    if (!map)
//    {
//        printf("free_map: map is NULL\n");
//        return;
//    }
        
//    i = 0;
//    while (map[i])
//    {
//        printf("free_map: freeing map[%d] at address %p\n", i, (void *)map[i]);
//        free(map[i]);
//        i++;
//    }
//    printf("free_map: freeing map at address %p\n", (void *)map);
//    free(map);
//}

static int handle_map_error(const char *message)
{
    ft_printf("%s", message);
    return (0);
}

int check_map(char **map)
{
    if (map == NULL)
        return (handle_map_error("Error\nMap is NULL\n"));
    if (check_map_size(map) == 0)
        return (handle_map_error("Error\nThe map is not rectangular or too large (32 × 16 is max)\n"));
    if (check_walls(map) == 0)
        return (handle_map_error("Error\nThe map is not surrounded by walls\n"));
    if (check_map_content(map) == 0)
        return (handle_map_error("Error\nThe map must contain 1 exit, at least 1 collectible, and 1 starting position\n"));
    if (check_path_availability(map, 0) == 0)
        return (handle_map_error("Error\nThe map is not valid. No ways\n"));
    return (1);
}