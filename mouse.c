/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:50:28 by relamine          #+#    #+#             */
/*   Updated: 2025/02/02 01:08:56 by saharchi         ###   ########.fr       */
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
	raycasting(p_map);
	animation(p_map);
}

void	cursorfunc(double xpos, double ypos, void *param)
{
	t_map			*p_map;

	p_map = (t_map *)param;
	if (p_map->m == 0)
		return ;
	if (xpos < 0 || ypos < 0 || xpos > WIDTH || ypos > HEIGHT)
	{
		p_map->prev_xpos = WIDTH / 2;
		mlx_set_mouse_pos(p_map->mlx, WIDTH / 2, HEIGHT / 2);
		return ;
	}
	p_map->player.rot_angle += (xpos - p_map->prev_xpos) * 0.003;
	if (p_map->player.rot_angle >= 2 * M_PI)
		p_map->player.rot_angle -= 2 * M_PI;
	if (p_map->player.rot_angle < 0)
		p_map->player.rot_angle += 2 * M_PI;
	p_map->prev_xpos = WIDTH / 2;
	mlx_set_mouse_pos(p_map->mlx, WIDTH / 2, HEIGHT / 2);
}

void	draw_wall_section(t_map *p_map, int i, int y, int color[4])
{
	mlx_put_pixel(p_map->map_img, i, y,
		get_rgba(color[0], color[1], color[2], color[3]));
}

void	draw_floor_ceiling(t_map *p_map, int i, int y)
{
	int	alpha;

	alpha = 255;
	if (y > (HEIGHT / 2))
	{
		alpha *= fmod(y, (HEIGHT / 2)) / (HEIGHT / 2);
		mlx_put_pixel(p_map->map_img, i, y,
			get_rgba(p_map->f.r, p_map->f.g, p_map->f.b, alpha));
	}
	else
		mlx_put_pixel(p_map->map_img, i, y,
			get_rgba(p_map->c.r, p_map->c.g, p_map->c.b, alpha));
}
