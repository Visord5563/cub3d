/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:51:36 by relamine          #+#    #+#             */
/*   Updated: 2025/01/29 21:36:42 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(t_map *p_map, double x, double y, int key_use)
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
			if (p_map->map[j][map_x_start] == 'D' && key_use != 2)
				return (1);
			if ((p_map->map[j][map_x_start] == 'D' && (p_map->door.is_open)))
			{
				p_map->map[j][map_x_start] = 'O';
				return (1);
			}
			else if ((p_map->map[j][map_x_start] == 'O') && (!p_map->door.is_open))
			{
				p_map->map[j][map_x_start] = 'D';
				return (1);
			}
			if (p_map->map[j][map_x_start] == '1')
				return (1);
			j++;
		}
		map_x_start++;
	}
	if (key_use == 2)
	{
		p_map->door.is_open = p_map->door.tmp_is_open;
		return (1);
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
