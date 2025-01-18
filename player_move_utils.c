/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:51:36 by relamine          #+#    #+#             */
/*   Updated: 2025/01/18 09:28:47 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(t_map *p_map, double x, double y)
{
	int	map_x_start;
	int	map_y_start;
	int	map_x_end;
	int	map_y_end;
	int	j;

	map_x_start = floor((x - PLAYER_SIZE / 2) / TILE_SIZE);
	map_y_start = floor((y - PLAYER_SIZE / 2) / TILE_SIZE);
	map_x_end = floor((x + PLAYER_SIZE / 2) / TILE_SIZE);
	map_y_end = floor((y + PLAYER_SIZE / 2) / TILE_SIZE);
	while (map_x_start <= map_x_end)
	{
		j = map_y_start;
		while (j <= map_y_end)
		{
			if (j < 0 || map_x_start < 0
				|| j >= p_map->map_height || map_x_start >= p_map->map_width)
				return (1);
			if (p_map->map[j][map_x_start] == '1')
				return (1);
			j++;
		}
		map_x_start++;
	}
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
