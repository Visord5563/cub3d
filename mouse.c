/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:50:28 by relamine          #+#    #+#             */
/*   Updated: 2025/01/29 21:51:54 by relamine         ###   ########.fr       */
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
