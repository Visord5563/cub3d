/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:35:21 by saharchi          #+#    #+#             */
/*   Updated: 2025/02/02 00:46:49 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall_texture(t_map *p_map, double distance,
	int i, mlx_texture_t *texture)
{
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	int		y;
	int		color[4];

	get_wall(distance, &wall_height, &wall_top, &wall_bottom);
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= wall_top && y <= wall_bottom && y < HEIGHT)
		{
			_texters(1.0 - (wall_bottom - y) / wall_height, color,
				texture, p_map);
			if (distance >= TILE_SIZE)
				color[3] *= (TILE_SIZE / distance);
			draw_wall_section(p_map, i, y, color);
		}
		else
			draw_floor_ceiling(p_map, i, y);
		y++;
	}
}

mlx_texture_t	*choose_texture(t_map *p_map, int side, double *distance)
{
	mlx_texture_t	*texture;

	texture = ft_whiche_texture(p_map->textures, p_map->ray_angle, side);
	if (p_map->door.is_dor_v || p_map->door.is_dor_h)
		texture = p_map->textures[4];
	*distance *= cos(p_map->ray_angle - p_map->player.rot_angle);
	return (texture);
}

void	rander_texter(t_map *p_map, double distance, int i, int side)
{
	mlx_texture_t	*texture;

	texture = choose_texture(p_map, side, &distance);
	render_wall_texture(p_map, distance, i, texture);
}

void	check_ray(t_map *p_map, double *distance, int *side)
{
	double	distance_h;
	double	distance_v;

	p_map->door.is_dor_h = 0;
	p_map->door.is_dor_v = 0;
	p_map->ray_angle = fmod(p_map->ray_angle, 2 * M_PI);
	if (p_map->ray_angle < 0)
		p_map->ray_angle += 2 * M_PI;
	distance_h = get_horizontal(p_map, p_map->ray_angle);
	distance_v = get_vertical(p_map, p_map->ray_angle);
	if (distance_h != -1 && (distance_v == -1 || distance_h < distance_v))
	{
		p_map->y_inter = -1;
		*distance = distance_h;
		*side = 1;
		p_map->door.is_dor_v = 0;
	}
	else
	{
		p_map->x_inter = -1;
		*distance = distance_v;
		p_map->door.is_dor_h = 0;
	}
}

void	raycasting(t_map *p_map)
{
	double	distance;
	double	angle_increment ;
	int		i;
	int		side;

	i = 0;
	distance = 0;
	angle_increment = FOV * (M_PI / 180) / WIDTH;
	p_map->ray_angle = p_map->player.rot_angle - (FOV * (M_PI / 180) / 2);
	while (i < WIDTH)
	{
		side = 0;
		check_ray(p_map, &distance, &side);
		rander_texter(p_map, distance, i, side);
		p_map->ray_angle += angle_increment;
		i++;
	}
	draw_minimap(p_map);
}
