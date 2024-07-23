/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:31:49 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/24 02:25:44 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"
#include <stdlib.h> // Для использования функции exit

int calculate_tile_size(int map_width, int map_height)
{
    int tile_size_width = WINDOW_WIDTH / map_width;
    int tile_size_height = WINDOW_HEIGHT / map_height;
    int tile_size = fmin(tile_size_width, tile_size_height);
    
    return fmin(tile_size, MAX_TILE_SIZE);
}

void nearest_neighbor_scale(char *src_data, char *dst_data, int src_width, int src_height, int dst_width, int dst_height, int bpp, int src_size_line, int dst_size_line)
{
    for (int y = 0; y < dst_height; y++)
    {
        for (int x = 0; x < dst_width; x++)
        {
            int src_x = x * src_width / dst_width;
            int src_y = y * src_height / dst_height;
            int src_pixel_index = src_y * src_size_line + src_x * (bpp / 8);
            int dst_pixel_index = y * dst_size_line + x * (bpp / 8);

            for (int i = 0; i < bpp / 8; i++)
            {
                dst_data[dst_pixel_index + i] = src_data[src_pixel_index + i];
            }
        }
    }
}

void scale_image(void *mlx, void **img, int old_width, int old_height, int new_width, int new_height)
{
    void *new_img;
    int bpp, src_size_line, src_endian;
    int dst_size_line, dst_endian;
    char *old_data;
    char *new_data;

    new_img = mlx_new_image(mlx, new_width, new_height);
    old_data = mlx_get_data_addr(*img, &bpp, &src_size_line, &src_endian);
    new_data = mlx_get_data_addr(new_img, &bpp, &dst_size_line, &dst_endian);

    nearest_neighbor_scale(old_data, new_data, old_width, old_height, new_width, new_height, bpp, src_size_line, dst_size_line);

    mlx_destroy_image(mlx, *img);
    *img = new_img;
}

void load_textures(t_data *data, int tile_size)
{
    int img_width = 128;
    int img_height = 128;

    data->img_wall = mlx_xpm_file_to_image(data->mlx, "./assets/wall.xpm", &img_width, &img_height);
    if (!data->img_wall)
        printf("Error loading wall texture\n");
    scale_image(data->mlx, &data->img_wall, img_width, img_height, tile_size, tile_size);

    data->img_floor = mlx_xpm_file_to_image(data->mlx, "./assets/floor.xpm", &img_width, &img_height);
    if (!data->img_floor)
        printf("Error loading floor texture\n");
    scale_image(data->mlx, &data->img_floor, img_width, img_height, tile_size, tile_size);

    data->img_player = mlx_xpm_file_to_image(data->mlx, "./assets/player.xpm", &img_width, &img_height);
    if (!data->img_player)
        printf("Error loading player texture\n");
    scale_image(data->mlx, &data->img_player, img_width, img_height, tile_size, tile_size);

    data->img_exit = mlx_xpm_file_to_image(data->mlx, "./assets/exit.xpm", &img_width, &img_height);
    if (!data->img_exit)
        printf("Error loading exit texture\n");
    scale_image(data->mlx, &data->img_exit, img_width, img_height, tile_size, tile_size);

    data->img_collectible = mlx_xpm_file_to_image(data->mlx, "./assets/collectible.xpm", &img_width, &img_height);
    if (!data->img_collectible)
        printf("Error loading collectible texture\n");
    scale_image(data->mlx, &data->img_collectible, img_width, img_height, tile_size, tile_size);
}

void draw_map(t_data *data)
{ 
    int i;
    int j;
    int tile_size = data->tile_size;  // Используем размер тайлов из структуры данных

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            printf("Drawing at (%d, %d): %c\n", i, j, data->map[i][j]);
            if (data->map[i][j] == '1')
                mlx_put_image_to_window(data->mlx, data->win, data->img_wall, j * tile_size, i * tile_size);
            else if (data->map[i][j] == '0')
                mlx_put_image_to_window(data->mlx, data->win, data->img_floor, j * tile_size, i * tile_size);
            else if (data->map[i][j] == 'P')
                mlx_put_image_to_window(data->mlx, data->win, data->img_player, j * tile_size, i * tile_size);
            else if (data->map[i][j] == 'E')
                mlx_put_image_to_window(data->mlx, data->win, data->img_exit, j * tile_size, i * tile_size);
            else if (data->map[i][j] == 'C')
                mlx_put_image_to_window(data->mlx, data->win, data->img_collectible, j * tile_size, i * tile_size);
            j++;
        }
        i++;
    }
}

int find_player(t_data *data, int *x, int *y)
{
    for (int i = 0; i < data->height / data->tile_size; i++)
    {
        for (int j = 0; j < data->width / data->tile_size; j++)
        {
            if (data->map[i][j] == 'P')
            {
                *x = j;
                *y = i;
                return 1;
            }
        }
    }
    return 0;
}

int check_win(t_data *data)
{
    for (int i = 0; i < data->height / data->tile_size; i++)
    {
        for (int j = 0; j < data->width / data->tile_size; j++)
        {
            if (data->map[i][j] == 'C')
            {
                return 0;
            }
        }
    }
    return 1;
}

void end_game(t_data *data)
{
    printf("Игра закончена!\n");
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}

int key_hook(int keycode, t_data *data)
{
    int x, y;

    find_player(data, &x, &y);
    if (keycode == 53) // Q key to quit
    {
        end_game(data);
    }
    else if (keycode == 13) // W key
    {
        if (data->map[y-1][x] != '1')
        {
            if (data->map[y-1][x] == 'C') data->map[y-1][x] = '0';
            data->map[y][x] = '0';
            data->map[y-1][x] = 'P';
        }
    }
    else if (keycode == 0) // A key
    {
        if (data->map[y][x-1] != '1')
        {
            if (data->map[y][x-1] == 'C') data->map[y][x-1] = '0';
            data->map[y][x] = '0';
            data->map[y][x-1] = 'P';
        }
    }
    else if (keycode == 1) // S key
    {
        if (data->map[y+1][x] != '1')
        {
            if (data->map[y+1][x] == 'C') data->map[y+1][x] = '0';
            data->map[y][x] = '0';
            data->map[y+1][x] = 'P';
        }
    }
    else if (keycode == 2) // D key
    {
        if (data->map[y][x+1] != '1')
        {
            if (data->map[y][x+1] == 'C') data->map[y][x+1] = '0';
            data->map[y][x] = '0';
            data->map[y][x+1] = 'P';
        }
    }

    if (data->map[y][x] == 'E' && check_win(data))
    {
        end_game(data);
    }
    
    draw_map(data);
    return 0;
}

void game_start(char **map)
{
    t_data data;
    int tile_size;

    get_map_size(map, &data.width, &data.height);
    tile_size = calculate_tile_size(data.width, data.height);

    data.tile_size = tile_size;  // Сохраняем размер тайлов в структуре данных
    data.height *= tile_size;
    data.width *= tile_size;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.width, data.height, "The Elon Game");

    load_textures(&data, tile_size);

    data.map = map;
    draw_map(&data);

    mlx_key_hook(data.win, key_hook, &data);
    mlx_loop(data.mlx);
}


// ЭТО РАБОТАЕТ
//int calculate_tile_size(int map_width, int map_height)
//{
//    int tile_size_width = WINDOW_WIDTH / map_width;
//    int tile_size_height = WINDOW_HEIGHT / map_height;
//    int tile_size = fmin(tile_size_width, tile_size_height);
    
//    return fmin(tile_size, MAX_TILE_SIZE);
//}

//void nearest_neighbor_scale(char *src_data, char *dst_data, int src_width, int src_height, int dst_width, int dst_height, int bpp, int src_size_line, int dst_size_line)
//{
//    for (int y = 0; y < dst_height; y++)
//    {
//        for (int x = 0; x < dst_width; x++)
//        {
//            int src_x = x * src_width / dst_width;
//            int src_y = y * src_height / dst_height;
//            int src_pixel_index = src_y * src_size_line + src_x * (bpp / 8);
//            int dst_pixel_index = y * dst_size_line + x * (bpp / 8);

//            for (int i = 0; i < bpp / 8; i++)
//            {
//                dst_data[dst_pixel_index + i] = src_data[src_pixel_index + i];
//            }
//        }
//    }
//}

//void scale_image(void *mlx, void **img, int old_width, int old_height, int new_width, int new_height)
//{
//    void *new_img;
//    int bpp, src_size_line, src_endian;
//    int dst_size_line, dst_endian;
//    char *old_data;
//    char *new_data;

//    new_img = mlx_new_image(mlx, new_width, new_height);
//    old_data = mlx_get_data_addr(*img, &bpp, &src_size_line, &src_endian);
//    new_data = mlx_get_data_addr(new_img, &bpp, &dst_size_line, &dst_endian);

//    nearest_neighbor_scale(old_data, new_data, old_width, old_height, new_width, new_height, bpp, src_size_line, dst_size_line);

//    mlx_destroy_image(mlx, *img);
//    *img = new_img;
//}

//void load_textures(t_data *data, int tile_size)
//{
//    int img_width = 128;
//    int img_height = 128;

//    data->img_wall = mlx_xpm_file_to_image(data->mlx, "./assets/wall.xpm", &img_width, &img_height);
//    if (!data->img_wall)
//        printf("Error loading wall texture\n");
//    scale_image(data->mlx, &data->img_wall, img_width, img_height, tile_size, tile_size);

//    data->img_floor = mlx_xpm_file_to_image(data->mlx, "./assets/floor.xpm", &img_width, &img_height);
//    if (!data->img_floor)
//        printf("Error loading floor texture\n");
//    scale_image(data->mlx, &data->img_floor, img_width, img_height, tile_size, tile_size);

//    data->img_player = mlx_xpm_file_to_image(data->mlx, "./assets/player.xpm", &img_width, &img_height);
//    if (!data->img_player)
//        printf("Error loading player texture\n");
//    scale_image(data->mlx, &data->img_player, img_width, img_height, tile_size, tile_size);

//    data->img_exit = mlx_xpm_file_to_image(data->mlx, "./assets/exit.xpm", &img_width, &img_height);
//    if (!data->img_exit)
//        printf("Error loading exit texture\n");
//    scale_image(data->mlx, &data->img_exit, img_width, img_height, tile_size, tile_size);

//    data->img_collectible = mlx_xpm_file_to_image(data->mlx, "./assets/collectible.xpm", &img_width, &img_height);
//    if (!data->img_collectible)
//        printf("Error loading collectible texture\n");
//    scale_image(data->mlx, &data->img_collectible, img_width, img_height, tile_size, tile_size);
//}

//void draw_map(t_data *data)
//{ 
//    int i;
//    int j;
//    int tile_size = data->tile_size;  // Используем размер тайлов из структуры данных

//    i = 0;
//    while (data->map[i])
//    {
//        j = 0;
//        while (data->map[i][j])
//        {
//            printf("Drawing at (%d, %d): %c\n", i, j, data->map[i][j]);
//            if (data->map[i][j] == '1')
//                mlx_put_image_to_window(data->mlx, data->win, data->img_wall, j * tile_size, i * tile_size);
//            else if (data->map[i][j] == '0')
//                mlx_put_image_to_window(data->mlx, data->win, data->img_floor, j * tile_size, i * tile_size);
//            else if (data->map[i][j] == 'P')
//                mlx_put_image_to_window(data->mlx, data->win, data->img_player, j * tile_size, i * tile_size);
//            else if (data->map[i][j] == 'E')
//                mlx_put_image_to_window(data->mlx, data->win, data->img_exit, j * tile_size, i * tile_size);
//            else if (data->map[i][j] == 'C')
//                mlx_put_image_to_window(data->mlx, data->win, data->img_collectible, j * tile_size, i * tile_size);
//            j++;
//        }
//        i++;
//    }
//}

//void game_start(char **map)
//{
//    t_data data;
//    int tile_size;

//    get_map_size(map, &data.width, &data.height);
//    tile_size = calculate_tile_size(data.width, data.height);

//    data.tile_size = tile_size;  // Сохраняем размер тайлов в структуре данных
//    data.height *= tile_size;
//    data.width *= tile_size;

//    data.mlx = mlx_init();
//    data.win = mlx_new_window(data.mlx, data.width, data.height, "The Elon Game");
//    load_textures(&data, tile_size);

//    data.map = map;
//    draw_map(&data);

//    mlx_loop(data.mlx);
//}