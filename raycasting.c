/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:35:21 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/16 22:15:12 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_horizontal(t_map *p_map, double ray_angle)
{
    double x_inter = 0;
    double y_inter = 0;
    // double y_step = 0;
    // double x_step = 0;

    // if (sin(ray_angle) > 0)
    //     y_inter = (p_map->player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    // else 
    //     y_inter = (p_map->player.y / TILE_SIZE) * TILE_SIZE - 1;
    
    x_inter = p_map->player.x + (y_inter - p_map->player.y) / tan(ray_angle);

    
    
    while (x_inter >= 0 && x_inter < WIDTH * TILE_SIZE && y_inter >= 0 && y_inter < HEIGHT * TILE_SIZE)
    {
        if (p_map->map[(int)y_inter / TILE_SIZE][(int)x_inter / TILE_SIZE] != '1')
            return (sqrt(pow(x_inter - p_map->player.x, 2) + pow(y_inter -  p_map->player.y , 2)));
        y_inter += TILE_SIZE;
        x_inter = TILE_SIZE * tan(ray_angle);
    }
    return (-1);
}
int get_virtical(t_map *p_map, double ray_angle)
{
    double x_inter = 0;
    double y_inter = 0;
    // double y_step = 0;
    // double x_step = 0;

    // if (cos(ray_angle) > 0) 
    //     x_inter = (p_map->player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    // else 
    //     x_inter = (p_map->player.x / TILE_SIZE) * TILE_SIZE - 1;
    
    y_inter = p_map->player.y + (x_inter - p_map->player.x) * tan(ray_angle);
    while (x_inter >= 0 && x_inter < WIDTH * TILE_SIZE && y_inter >= 0 && y_inter < HEIGHT * TILE_SIZE)
    {
        if (p_map->map[(int)y_inter / TILE_SIZE][(int)x_inter / TILE_SIZE] != '1')
            return (sqrt(pow(x_inter - p_map->player.x , 2) + pow(y_inter -  p_map->player.y, 2)));
        y_inter += TILE_SIZE;
        x_inter = TILE_SIZE * tan(ray_angle);
    }
    
    return (-1);
}

void raycasting(t_map *p_map, mlx_t* mlx, mlx_image_t* map)
{
    double ray_angle[WIDTH];
    double first_ray = 0;
    int increment = 0;
    int convert = 0;
    int wall_height = 0;
    int wall_bottom = 0;
    int wall_top = 0;
    int i = 0;
    (void)mlx;
    (void)map;
    convert =  FOV * (M_PI / 180);
    first_ray = player_angle - ( convert / 2);
    increment = convert / WIDTH;


    int distance_h = 0;
    int distance_v = 0;
    while(i < WIDTH)
    {
        // mlx_delete_image(mlx, map);
        ray_angle[i] = first_ray + (i * increment);
        distance_v = get_virtical(p_map, ray_angle[i]);
        distance_h = get_horizontal(p_map, ray_angle[i]);
        printf("distance_h = %d distance_v = %d\n", distance_h, distance_v);
        if (distance_h < distance_v || (distance_v == -1 && distance_h != -1))
        {
            printf("horizontal\n");
            wall_height = (HEIGHT / distance_h);
            wall_top = (HEIGHT / 2) - (wall_height / 2);
            wall_bottom = (HEIGHT / 2) + (wall_height / 2);
            printf("wall_height = %d wall_bottom %d\n", wall_height, wall_bottom);
            while (wall_top < wall_bottom)
            {
                mlx_put_pixel(map, i, wall_top, get_rgba(241, 196, 15, 255));
                wall_top++;
            }
            
        }
        else
        {
            printf("virtical\n");
            wall_height = (HEIGHT / distance_v);
            wall_top = (HEIGHT / 2) - (wall_height / 2);
            wall_bottom = (HEIGHT / 2) + (wall_height / 2);
            while (wall_top < wall_bottom)
            {
                mlx_put_pixel(map, i, wall_top, get_rgba(241, 196, 15, 255));
                wall_top++;
            }
            // printf("wall_height = %d wall_bottom %d\n", wall_height, wall_bottom);
        }
        i++;
    }
}