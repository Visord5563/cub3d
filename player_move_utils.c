/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:51:36 by relamine          #+#    #+#             */
/*   Updated: 2025/01/29 22:30:40 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player_f(t_map *p_map)
{
	int	map_x_start;
	int	map_y_start;
	int	map_x_end;
	int	map_y_end;
	int	j;

	map_x_start = floor((p_map->player.x_double - p_map->p_sz / 2) / TILE_SIZE);
	map_y_start = floor((p_map->player.y_double - p_map->p_sz / 2) / TILE_SIZE);
	map_x_end = floor((p_map->player.x_double + p_map->p_sz / 2) / TILE_SIZE);
	map_y_end = floor((p_map->player.y_double + p_map->p_sz / 2) / TILE_SIZE);
	while (map_x_start <= map_x_end)
	{
		j = map_y_start;
		while (j <= map_y_end)
		{
			if (j < 0 || map_x_start < 0
				|| j >= p_map->map_height || map_x_start >= p_map->map_width)
				return (1);
			if (p_map->map[j][map_x_start] == 'O')
				return (1);
			j++;
		}
		map_x_start++;
	}
	return (0);
}

int	hit_wall_check(t_map *p_map, int x, int y, int key_use)
{
	if (y < 0 || x < 0 || y >= p_map->map_height || x >= p_map->map_width)
		return (1);
	if (p_map->map[y][x] == 'D' && key_use != 2)
		return (1);
	if (p_map->map[y][x] == 'D' && p_map->door.is_open)
	{
		p_map->map[y][x] = 'O';
		return (1);
	}
	else if (p_map->map[y][x] == 'O' && !p_map->door.is_open)
	{
		p_map->map[y][x] = 'D';
		return (1);
	}
	if (p_map->map[y][x] == '1')
		return (1);
	return (0);
}

int	hit_wall(t_map *p_map, double x, double y, int key_use)
{
	int	map_x_start;
	int	map_y_start;
	int	map_x_end;
	int	map_y_end;
	int	j;

	map_x_start = floor((x - p_map->p_sz / 2) / TILE_SIZE);
	map_y_start = floor((y - p_map->p_sz / 2) / TILE_SIZE);
	map_x_end = floor((x + p_map->p_sz / 2) / TILE_SIZE);
	map_y_end = floor((y + p_map->p_sz / 2) / TILE_SIZE);
	while (map_x_start <= map_x_end)
	{
		j = map_y_start;
		while (j <= map_y_end)
		{
			if (hit_wall_check(p_map, map_x_start, j, key_use))
				return (1);
			j++;
		}
		map_x_start++;
	}
	if (key_use == 2)
		return (p_map->door.is_open = p_map->door.tmp_is_open, 1);
	return (0);
}

void	close_win(void *param)
{
	t_map	*p_map;

	p_map = (t_map *)param;
	free_map(p_map);
	exit(0);
}

void	key_release(t_map *p_map)
{
	p_map->player.walk_dir = 0;
	p_map->player.turn_dir = 0;
	p_map->player.walk_side = 0;
}
