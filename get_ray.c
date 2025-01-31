/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:05:33 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/31 18:06:05 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall_h(t_map *p_map, int map_x, int map_y)
{
	if (p_map->map[map_y][map_x] == '1' || p_map->map[map_y][map_x] == 'D')
	{
		if (p_map->map[map_y][map_x] == 'D')
			p_map->door.is_dor_h = 1;
		p_map->x_inter = p_map->ray.x_inter;
		return (1);
	}
	return (0);
}

double	get_horizontal(t_map *p_map, double ray_angle)
{
	int	map_x;
	int	map_y;

	init_ray(p_map, ray_angle);
	get_y(p_map, ray_angle);
	while (p_map->ray.x_inter >= 0
		&& p_map->ray.x_inter < (p_map->map_width * TILE_SIZE)
		&& p_map->ray.y_inter >= 0
		&& p_map->ray.y_inter < (p_map->map_height * TILE_SIZE))
	{
		map_x = floor(p_map->ray.x_inter / TILE_SIZE);
		map_y = floor(p_map->ray.y_inter / TILE_SIZE);
		if (p_map->ray.facing_up)
			map_y -= 1;
		if (check_boundaries(p_map, map_x, map_y))
			return (-1);
		if (check_wall_h(p_map, map_x, map_y))
			return (calculate_distance(p_map));
		p_map->ray.x_inter += p_map->ray.x_step;
		p_map->ray.y_inter += p_map->ray.y_step;
	}
	return (-1);
}

int	check_wall_v(t_map *p_map, int map_x, int map_y)
{
	if (p_map->map[map_y][map_x] == '1' || p_map->map[map_y][map_x] == 'D')
	{
		if (p_map->map[map_y][map_x] == 'D')
			p_map->door.is_dor_v = 1;
		p_map->y_inter = p_map->ray.y_inter;
		return (1);
	}
	return (0);
}

double	get_vertical(t_map *p_map, double ray_angle)
{
	int	map_x;
	int	map_y;

	init_ray(p_map, ray_angle);
	get_x(p_map, ray_angle);
	while (p_map->ray.x_inter >= 0
		&& p_map->ray.x_inter < (p_map->map_width * TILE_SIZE)
		&& p_map->ray.y_inter >= 0
		&& p_map->ray.y_inter < (p_map->map_height * TILE_SIZE))
	{
		map_x = floor(p_map->ray.x_inter / TILE_SIZE);
		if (p_map->ray.facing_left)
			map_x -= 1;
		map_y = floor(p_map->ray.y_inter / TILE_SIZE);
		if (check_boundaries(p_map, map_x, map_y))
			return (-1);
		if (check_wall_v(p_map, map_x, map_y))
			return (calculate_distance(p_map));
		p_map->ray.x_inter += p_map->ray.x_step;
		p_map->ray.y_inter += p_map->ray.y_step;
	}
	return (-1);
}

void	get_wall(double distance, double *wall_height,
	double *wall_top, double *wall_bottom)
{
	int	dist_proj_plane;

	dist_proj_plane = (WIDTH / (2 * tan((FOV * M_PI / 180) / 2)));
	*wall_height = (TILE_SIZE * dist_proj_plane) / distance;
	*wall_top = (HEIGHT / 2) - (*wall_height / 2);
	*wall_bottom = *wall_top + *wall_height;
	if (*wall_top < 0)
		*wall_top = 0;
}
