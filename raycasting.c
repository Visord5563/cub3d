/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:35:21 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/19 21:44:26 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_horizontal(t_map *p_map, double ray_angle)
{
    double x_inter, y_inter, x_step, y_step;
    double player_x = p_map->player.x_double;
    double player_y = p_map->player.y_double;

    int rayfacingdown = 0;
    if (ray_angle > 0 && ray_angle < M_PI)
        rayfacingdown = 1;
    int rayfacingup = 0;
    if (!rayfacingdown)
        rayfacingup = 1;
    int rayfacingright = 0;
    if (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI)
        rayfacingright = 1;
    int rayfacingleft = 0;
    if (!rayfacingright)
        rayfacingleft = 1;

    y_step = TILE_SIZE;
    if (rayfacingup)
        y_step *= -1;
    x_step = TILE_SIZE / tan(ray_angle);
    if (rayfacingleft && x_step > 0)
        x_step *= -1;
    if (rayfacingright && x_step < 0)
        x_step *= -1;

    y_inter = floor(player_y / TILE_SIZE) * TILE_SIZE;
    if (rayfacingdown)
        y_inter += TILE_SIZE;
    x_inter = player_x + (y_inter - player_y) / tan(ray_angle);

    while (x_inter >= 0 && x_inter <( p_map->map_width * TILE_SIZE) && y_inter >= 0 && y_inter <( p_map->map_height * TILE_SIZE))
    {
        int map_x = floor(x_inter / TILE_SIZE);
        int map_y = floor(y_inter / TILE_SIZE);
        if (rayfacingup)
            map_y -= 1;
        
        if (map_y < 0 || map_x < 0 || map_y >= p_map->map_height || map_x >= p_map->map_width)
            return -1;
        if (p_map->map[map_y][map_x] == '1' || p_map->map[map_y][map_x] == 'D')
        {
            if (p_map->map[map_y][map_x] == 'D')
                p_map->door.is_dor_h = 1;
            p_map->x_inter = x_inter;
            return sqrt(pow(x_inter - player_x, 2) + pow(y_inter - player_y, 2));
        }

        x_inter += x_step;
        y_inter += y_step;
    }

    return -1;
}

double get_vertical(t_map *p_map, double ray_angle)
{
    double x_inter, y_inter, x_step, y_step;
    double player_x = p_map->player.x_double;
    double player_y = p_map->player.y_double;

    int rayfacingleft = 0;
    if (ray_angle > 0.5 * M_PI && ray_angle < 1.5 * M_PI)
        rayfacingleft = 1;
    int rayfacingright = 0;
    if (!rayfacingleft)
        rayfacingright = 1;
    int rayfacingdown = 0;
    if (ray_angle > 0 && ray_angle < M_PI)
        rayfacingdown = 1;
    int rayfacingup = 0;
    if (!rayfacingdown)
        rayfacingup = 1;

    x_step = TILE_SIZE;
    if (rayfacingleft)
        x_step *= -1;
    y_step = TILE_SIZE * tan(ray_angle);
    if (rayfacingup && y_step > 0)
        y_step *= -1;
    if (rayfacingdown && y_step < 0)
        y_step *= -1;

    x_inter = floor(player_x / TILE_SIZE) * TILE_SIZE;
    if (rayfacingright)
        x_inter += TILE_SIZE;
    y_inter = player_y + (x_inter - player_x) * tan(ray_angle);

    while (x_inter >= 0 && x_inter <( p_map->map_width * TILE_SIZE) && y_inter >= 0 && y_inter <( p_map->map_height * TILE_SIZE))
    {
        int map_x = floor(x_inter / TILE_SIZE);
        if (rayfacingleft)
            map_x -= 1;
        int map_y = floor(y_inter / TILE_SIZE);

        if (map_y < 0 || map_x < 0 || map_y >= p_map->map_height || map_x >= p_map->map_width)
            return -1;

        if (p_map->map[map_y][map_x] == '1' || p_map->map[map_y][map_x] == 'D')
        {
            if (p_map->map[map_y][map_x] == 'D')
                p_map->door.is_dor_v = 1;
            p_map->y_inter = y_inter;
            return sqrt(pow(x_inter - player_x, 2) + pow(y_inter - player_y, 2));
        }

        x_inter += x_step;
        y_inter += y_step;
    }

    return -1;
}


void raycasting(t_map *p_map)
{
    double ray_angle, distance_h, distance_v, distance;
    double wall_height, wall_top, wall_bottom;
    double angle_increment = FOV * (M_PI / 180) / WIDTH;
    int i = 0;
    int y;
    int color[4];

    ray_angle = p_map->player.rot_angle - (FOV * (M_PI / 180) / 2);
    mlx_texture_t *texture;

    while (i < WIDTH)
    {
        p_map->door.is_dor_h = 0;
        p_map->door.is_dor_v = 0;
        ray_angle = fmod(ray_angle, 2 * M_PI);
        if (ray_angle < 0)
            ray_angle += 2 * M_PI;

        distance_h = get_horizontal(p_map, ray_angle);
        distance_v = get_vertical(p_map, ray_angle);
        int side = 0;
        if (distance_h != -1 && (distance_v == -1 || distance_h < distance_v)) {
            p_map->y_inter = -1;
            distance = distance_h;
            side = 1;
            p_map->door.is_dor_v = 0;
        }
        else
        {
            p_map->x_inter = -1;
            distance = distance_v;
            p_map->door.is_dor_h = 0;
        }
        texture = ft_whiche_texture( p_map->textures, ray_angle, side);
        if (p_map->door.is_dor_v || p_map->door.is_dor_h)
                texture = p_map->textures[4];   


        distance *= cos(ray_angle - p_map->player.rot_angle);
        wall_height = (TILE_SIZE * DIST_PROJ_PLANE) / distance;
        wall_top = (HEIGHT / 2) - (wall_height / 2);
        wall_bottom = wall_top + wall_height;

        if (wall_top < 0)
            wall_top = 0;
        y = 0;
        while (y < HEIGHT)
        {
            if (y >= wall_top && y <= wall_bottom && y < HEIGHT)
            {
                _texters(1.0 - (wall_bottom - y) / wall_height, color, texture, p_map);
                mlx_put_pixel(p_map->map_img, i, y, get_rgba(color[0], color[1], color[2], color[3]));
            }
            else if (y > (HEIGHT / 2))
                mlx_put_pixel(p_map->map_img, i, y, get_rgba(p_map->c.r, p_map->c.g, p_map->c.b, 255));
            else
                mlx_put_pixel(p_map->map_img, i, y, get_rgba(p_map->f.r, p_map->f.g, p_map->f.b, 255));
            y++;
        }
        ray_angle += angle_increment;
        i++;
    }
    draw_minimap(p_map);
}
