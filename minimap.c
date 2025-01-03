/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:54:27 by relamine          #+#    #+#             */
/*   Updated: 2025/01/01 19:06:29 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_player(t_map *p_map, int x1, int y1)
{
    mlx_image_t *player;
    int player_width;
    int player_height;
    int player_x;
    int player_y;
    int x, y;

    player_width = p_map->cell_width / 2;
    player_height = p_map->cell_height / 2;

    player_x = (x1 * p_map->cell_width) + (fmod(p_map->player.x_double, TILE_SIZE) / TILE_SIZE * p_map->cell_width) / 2;
    player_y = (y1 * p_map->cell_height) + (fmod(p_map->player.y_double, TILE_SIZE) / TILE_SIZE * p_map->cell_height) / 2;

    if (p_map->player.player)
	{
        mlx_delete_image(p_map->mlx, p_map->player.player);
    }

    player = mlx_new_image(p_map->mlx, player_width, player_height);
    if (!player || mlx_image_to_window(p_map->mlx, player, player_x, player_y) < 0) {
        printf("Error\n");
        free_map(p_map);
        exit(1);
    }

    y = 0;
    while (y < player_height) {
        x = 0;
        while (x < player_width) {
            mlx_put_pixel(player, x, y, get_rgba(241, 196, 15, 255));
            x++;
        }
        y++;
    }

    p_map->player.player = player;
}


void draw_minimap_cell(t_map *p_map, mlx_image_t*img, int x, int y, int x_px, int y_px)
{
    int color;
    int y_map;
    int x_map;
	int x_pixel;
	int y_pixel;

	if (x == (int)(p_map->player.x_double / TILE_SIZE) && y == (int)(p_map->player.y_double / TILE_SIZE))
		render_player(p_map, x_px, y_px);
	color = get_cell_color(p_map, x, y);
	y_map =0;
	while (y_map < p_map->cell_height)
	{
		x_map = 0;
		while (x_map < p_map->cell_width)
		{
			x_pixel = x_px * p_map->cell_width + x_map;
			y_pixel = y_px * p_map->cell_height + y_map;
			if ((x_map == 0 || y_map == 0) && p_map->map[y][x] != ' ')
				mlx_put_pixel(img, x_pixel, y_pixel, get_rgba(0, 0, 0, 100));
			else
				mlx_put_pixel(img, x_pixel, y_pixel, color);
			x_map++;
		}
		y_map++;
	}
}

void draw_minimap(t_map *p_map, mlx_image_t* img)
{
	int y_top;
	int y_bottom;
	int x_right;
	int x_left;
	int player_x;
	int player_y;
	int width_minimap;
	int height_minimap;

	ft_memset(p_map->minimap->pixels, 0, p_map->minimap->width * p_map->minimap->height * sizeof(int32_t));
	player_x = ((p_map->player.x_double / TILE_SIZE));
	player_y = ((p_map->player.y_double / TILE_SIZE));
	height_minimap = (p_map->map_height) / 2;
	width_minimap = (p_map->map_width) / 2;
	p_map->cell_height = M_HEIGHT / height_minimap;
	p_map->cell_width = M_WIDTH /  width_minimap;
	y_top = player_y - (height_minimap / 2);
	y_bottom =  y_top + height_minimap;
	if (y_top < 0)
	{
		y_top = 0;
		y_bottom = height_minimap;
	}
	else if (y_bottom > p_map->map_height)
	{
		y_bottom = p_map->map_height;
		y_top = y_bottom - height_minimap;
	}

	while (y_top < y_bottom)
	{
		x_left = player_x - (width_minimap / 2);
		x_right = x_left + width_minimap ;
		if (x_left < 0)
		{
			x_left = 0;
			x_right = width_minimap;
		}
		if (x_right > p_map->map_width)
		{
			x_right = p_map->map_width;
			x_left = x_right - width_minimap;
		}
		while (x_left < x_right)
		{
			draw_minimap_cell(p_map, img, x_left, y_top, x_left - (x_right - width_minimap),  y_top - (y_bottom - height_minimap));
			x_left++;
		}
		y_top++;
	}
	return ;
}

void ft_minimap(t_map *p_map)
{
	p_map->minimap = mlx_new_image(p_map->mlx, M_WIDTH, M_HEIGHT);
	if (!p_map->minimap || (mlx_image_to_window(p_map->mlx, p_map->minimap, 0, 0) < 0))
	{
		printf("Error\n");
		free_map(p_map);
		exit(1);
	}
}
