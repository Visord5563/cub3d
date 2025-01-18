/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 07:05:59 by relamine          #+#    #+#             */
/*   Updated: 2025/01/18 08:40:54 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_map *p_map, int x1, int y1)
{
	int	player_x;
	int	player_y;
	int	x_start;
	int	y_start;

	player_x = (x1 * p_map->minimap.cell_w) + (fmod(p_map->player.x_double,
				TILE_SIZE) / TILE_SIZE * p_map->minimap.cell_w);
	player_y = (y1 * p_map->minimap.cell_h) + (fmod(p_map->player.y_double,
				TILE_SIZE) / TILE_SIZE * p_map->minimap.cell_h);
	x_start = player_x - (p_map->player.width / 2);
	y_start = player_y - (p_map->player.height / 2);
	p_map->player.img->instances[0].x = x_start + MOVE_MAP;
	p_map->player.img->instances[0].y = y_start + MOVE_MAP;
	draw_ray_with_angle(player_x + MOVE_MAP, player_y + MOVE_MAP, p_map);
}

void	draw_minimap_cell_pixels(t_map *p_map,
	t_minimap_vars vars, int y_map, int color)
{
	int	x_map;
	int	x_pixel;
	int	y_pixel;

	x_map = 0;
	while (x_map < p_map->minimap.cell_w)
	{
		x_pixel = vars.x_scale * p_map->minimap.cell_w + x_map;
		y_pixel = vars.y_scale * p_map->minimap.cell_h + y_map;
		if ((x_map == 0 || y_map == 0)
			&& p_map->map[vars.y_top][vars.x_left] != ' ')
			mlx_put_pixel(p_map->minimap.img, x_pixel,
				y_pixel, get_rgba(0, 0, 0, 100));
		else if (p_map->map[vars.y_top][vars.x_left] == 'D')
			mlx_put_pixel(p_map->minimap.img, x_pixel, y_pixel, 0);
		else
			mlx_put_pixel(p_map->minimap.img, x_pixel, y_pixel, color);
		x_map++;
	}
}

void	draw_minimap_cell(t_map *p_map, t_minimap_vars	vars)
{
	int	color;
	int	y_map;

	if (vars.x_left == (int)(p_map->player.x_double / TILE_SIZE)
		&& vars.y_top == (int)(p_map->player.y_double / TILE_SIZE))
		render_player(p_map, vars.x_scale, vars.y_scale);
	color = get_cell_color(p_map, vars.x_left, vars.y_top);
	y_map = 0;
	while (y_map < p_map->minimap.cell_h)
	{
		draw_minimap_cell_pixels(p_map, vars, y_map, color);
		y_map++;
	}
}

void	draw_minimap_row(t_map *p_map, t_minimap_vars vars)
{
	vars.x_left = vars.player_x - (p_map->minimap.base_width / 2);
	vars.x_right = vars.x_left + p_map->minimap.base_width;
	if (vars.x_left < 0)
	{
		vars.x_left = 0;
		vars.x_right = p_map->minimap.base_width;
	}
	if (vars.x_right > p_map->map_width)
	{
		vars.x_right = p_map->map_width;
		vars.x_left = vars.x_right - p_map->minimap.base_width;
	}
	while (vars.x_left < vars.x_right)
	{
		vars.x_scale = vars.x_left - (vars.x_right - p_map->minimap.base_width);
		vars.y_scale = vars.y_top
			- (vars.y_bottom - p_map->minimap.base_height);
		draw_minimap_cell(p_map, vars);
		vars.x_left++;
	}
}

void	draw_minimap(t_map *p_map)
{
	t_minimap_vars	vars;

	vars.player_x = ((p_map->player.x_double / TILE_SIZE));
	vars.player_y = ((p_map->player.y_double / TILE_SIZE));
	vars.y_top = vars.player_y - (p_map->minimap.base_height / 2);
	vars.y_bottom = vars.y_top + p_map->minimap.base_height;
	if (vars.y_top < 0)
	{
		vars.y_top = 0;
		vars.y_bottom = p_map->minimap.base_height;
	}
	else if (vars.y_bottom > p_map->map_height)
	{
		vars.y_bottom = p_map->map_height;
		vars.y_top = vars.y_bottom - p_map->minimap.base_height;
	}
	while (vars.y_top < vars.y_bottom)
	{
		draw_minimap_row(p_map, vars);
		vars.y_top++;
	}
}
