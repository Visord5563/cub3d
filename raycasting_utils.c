/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:02:58 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/31 18:03:48 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_map *p_map, double ray_angle)
{
	p_map->ray.facing_down = 0;
	p_map->ray.facing_up = 0;
	p_map->ray.facing_right = 0;
	p_map->ray.facing_left = 0;
	p_map->ray.player_x = p_map->player.x_double;
	p_map->ray.player_y = p_map->player.y_double;
	p_map->ray.x_step = 0;
	p_map->ray.y_step = 0;
	if (ray_angle > 0 && ray_angle < M_PI)
		p_map->ray.facing_down = 1;
	if (!p_map->ray.facing_down)
		p_map->ray.facing_up = 1;
	if (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI)
		p_map->ray.facing_right = 1;
	if (!p_map->ray.facing_right)
		p_map->ray.facing_left = 1;
}

void	get_y(t_map *p_map, double ray_angle)
{
	double	player_x;
	double	player_y;

	player_x = p_map->ray.player_x;
	player_y = p_map->ray.player_y;
	p_map->ray.y_step = TILE_SIZE;
	if (p_map->ray.facing_up)
		p_map->ray.y_step *= -1;
	p_map->ray.x_step = TILE_SIZE / tan(ray_angle);
	if (p_map->ray.facing_left && p_map->ray.x_step > 0)
		p_map->ray.x_step *= -1;
	if (p_map->ray.facing_right && p_map->ray.x_step < 0)
		p_map->ray.x_step *= -1;
	p_map->ray.y_inter = floor(player_y / TILE_SIZE) * TILE_SIZE;
	if (p_map->ray.facing_down)
		p_map->ray.y_inter += TILE_SIZE;
	p_map->ray.x_inter = player_x
		+ (p_map->ray.y_inter - player_y) / tan(ray_angle);
}

void	get_x(t_map *p_map, double ray_angle)
{
	double	player_x;
	double	player_y;

	player_x = p_map->ray.player_x;
	player_y = p_map->ray.player_y;
	p_map->ray.x_step = TILE_SIZE;
	if (p_map->ray.facing_left)
		p_map->ray.x_step *= -1;
	p_map->ray.y_step = TILE_SIZE * tan(ray_angle);
	if (p_map->ray.facing_up && p_map->ray.y_step > 0)
		p_map->ray.y_step *= -1;
	if (p_map->ray.facing_down && p_map->ray.y_step < 0)
		p_map->ray.y_step *= -1;
	p_map->ray.x_inter = floor(player_x / TILE_SIZE) * TILE_SIZE;
	if (p_map->ray.facing_right)
		p_map->ray.x_inter += TILE_SIZE;
	p_map->ray.y_inter = player_y
		+ (p_map->ray.x_inter - player_x) * tan(ray_angle);
}

int	check_boundaries(t_map *p_map, int map_x, int map_y)
{
	if (map_y < 0 || map_x < 0 || map_y >= p_map->map_height
		|| map_x >= p_map->map_width)
		return (1);
	return (0);
}

double	calculate_distance(t_map *p_map)
{
	return (sqrt(pow(p_map->ray.x_inter - p_map->ray.player_x, 2)
			+ pow(p_map->ray.y_inter - p_map->ray.player_y, 2)));
}
