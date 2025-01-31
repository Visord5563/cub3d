/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:50:28 by relamine          #+#    #+#             */
/*   Updated: 2025/01/31 18:37:07 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	animation(t_map *map)
{
	int	current_frame;
	int	previous_frame;

	current_frame = map->i % 30;
	previous_frame = (current_frame - 1 + 30) % 30;
	map->player_img[current_frame]->enabled = true;
	map->player_img[previous_frame]->enabled = false;
	map->i = (map->i + 1) % 30;
}

void	exec(void *param)
{
	t_map	*p_map;

	p_map = (t_map *)param;
	animation(p_map);
}

void	cursorfunc(double xpos, double ypos, void *param)
{
	t_map			*p_map;
	double			delta_x;
	double			rotation_scale;
	static double	prev_xpos;
	static double	avg_delta_x;

	rotation_scale = 0.003;
	p_map = (t_map *)param;
	if (xpos < 0 || ypos < 0)
		xpos = 0;
	if (xpos > WIDTH || ypos > HEIGHT)
		xpos = WIDTH;
	delta_x = xpos - prev_xpos;
	prev_xpos = xpos;
	avg_delta_x = 0.9 * avg_delta_x + 0.2 * delta_x;
	p_map->player.rot_angle += avg_delta_x * rotation_scale;
	if (p_map->player.rot_angle >= 2 * M_PI)
		p_map->player.rot_angle -= 2 * M_PI;
	if (p_map->player.rot_angle < 0)
		p_map->player.rot_angle += 2 * M_PI;
	if (fabs(delta_x) > 1)
		raycasting(p_map);
}

void	draw_wall_section(t_map *p_map, int i, int y, int color[4])
{
	mlx_put_pixel(p_map->map_img, i, y,
		get_rgba(color[0], color[1], color[2], color[3]));
}

void	draw_floor_ceiling(t_map *p_map, int i, int y)
{
	if (y > (HEIGHT / 2))
		mlx_put_pixel(p_map->map_img, i, y,
			get_rgba(p_map->c.r, p_map->c.g, p_map->c.b, 255));
	else
		mlx_put_pixel(p_map->map_img, i, y,
			get_rgba(p_map->f.r, p_map->f.g, p_map->f.b, 255));
}
