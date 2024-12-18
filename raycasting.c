/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:35:21 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/18 23:43:16 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_horizontal(t_map *p_map, double ray_angle)
{
    double x_inter, y_inter, x_step , y_step;
    int player_x = p_map->player.x * TILE_SIZE + TILE_SIZE / 2;
    int player_y = p_map->player.y * TILE_SIZE + TILE_SIZE / 2;
    int ray;
    
    if (sin(ray_angle) < 0) {
        ray = 1;
        y_step = -TILE_SIZE;
        y_inter = ((player_y / TILE_SIZE) * TILE_SIZE) - 1;
    } else {
        ray = 0;
        y_step = TILE_SIZE;
        y_inter = ((player_y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
    }
    if (cos(ray_angle) < 0)
    {
        x_step = -fabs(TILE_SIZE / tan(ray_angle)); 
    } else {
        x_step = fabs(TILE_SIZE / tan(ray_angle)); 
    }
     x_inter = player_x + (y_inter - player_y) / tan(ray_angle); 
    while (x_inter >= 0 && x_inter < WIDTH && y_inter >= 0 && y_inter < HEIGHT)
    {
        int map_x = (int)(x_inter / TILE_SIZE);
        int map_y = (int)(y_inter / TILE_SIZE);

        if (p_map->map[map_y][map_x] == '1')
            return sqrt(pow(x_inter - player_x, 2) + pow(y_inter - player_y, 2));

        x_inter += x_step;
        y_inter += y_step;
    }

    return -1;
}


double get_vertical(t_map *p_map, double ray_angle)
{
    double x_inter, y_inter, x_step , y_step ;
    int player_x = p_map->player.x * TILE_SIZE + TILE_SIZE / 2;
    int player_y = p_map->player.y * TILE_SIZE + TILE_SIZE / 2;
    int ray;
    if (cos(ray_angle) < 0)
    {
        ray = 1;
        x_step = -TILE_SIZE;
        x_inter = ((player_x / TILE_SIZE) * TILE_SIZE) - 1;
    } else {
        ray = 0;
        x_step = TILE_SIZE;
        x_inter = ((player_x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
    }
    if (sin(ray_angle) < 0)
    {
        y_step = -fabs(TILE_SIZE * tan(ray_angle));
    } else {
        y_step = fabs(TILE_SIZE * tan(ray_angle));
    }
    y_inter = player_y + (x_inter - player_x) * tan(ray_angle);
    while (x_inter >= 0 && x_inter < WIDTH && y_inter >= 0 && y_inter < HEIGHT)
    {
        int map_x = (int)(x_inter / TILE_SIZE);
        int map_y = (int)(y_inter / TILE_SIZE);
        if (map_y >= ft_count(p_map->map) || (size_t)map_x >= ft_strlen(p_map->map[map_y]))
            return -1;
        if (p_map->map[map_y][map_x] == '1')
            return sqrt(pow(x_inter - player_x, 2) + pow(y_inter - player_y, 2));

        x_inter += x_step;
        y_inter += y_step;
    }

    return -1; 
}


void raycasting(t_map *p_map, mlx_t* mlx, mlx_image_t* map)
{
    (void)mlx;
    double ray_angle;
    double distance_h, distance_v, distance;
    double wall_height, wall_top, wall_bottom;
    double angle_increment = FOV * (M_PI / 180) / WIDTH; 
    int i = 0;

    ray_angle = player_angle - (FOV * (M_PI / 180) / 2);

    while (i < WIDTH)
    {
        ray_angle = fmod(ray_angle + (2 * M_PI), 2 * M_PI);
        distance_h = get_horizontal(p_map, ray_angle);
        distance_v = get_vertical(p_map, ray_angle);

        if (distance_h != -1 && (distance_v == -1 || distance_h < distance_v))
            distance = distance_h;
        else
            distance = distance_v;
        distance *= cos(ray_angle - player_angle);
        wall_height = (TILE_SIZE * DIST_PROJ_PLANE) / distance;
        wall_top = (HEIGHT / 2) - (wall_height / 2);
        wall_bottom = wall_top + wall_height;
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom > HEIGHT) wall_bottom = HEIGHT;
        int y = (int)wall_top;
        while (y < (int)wall_bottom)
        {
            mlx_put_pixel(map, i, y, get_rgba(241, 196, 15, 255));
            y++;
        }
        ray_angle += angle_increment;
        i++;
    }
}

