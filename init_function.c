/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:24:37 by relamine          #+#    #+#             */
/*   Updated: 2025/01/29 22:30:53 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->textures[i])
			map->textures[i] = NULL;
		i++;
	}
}

void	init_map(t_map **p_map)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (printf("Error\n"), exit(1), (void)0);
	map->f.r = -1;
	map->f.g = -1;
	map->f.b = -1;
	map->c.r = -1;
	map->c.g = -1;
	map->c.b = -1;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->d = NULL;
	map->map = NULL;
	map->map_img = NULL;
	map->minimap.img = NULL;
	map->player.img = NULL;
	map->mlx = NULL;
	map->fd = -1;
	map->i = 0;
	init_textures(map);
	*p_map = map;
}

void	get_posplayer(t_map *p_map, int y, int x)
{
	if (p_map->map[y][x] == 'N')
		p_map->player.rot_angle = 3 * M_PI / 2;
	if (p_map->map[y][x] == 'S')
		p_map->player.rot_angle = M_PI / 2;
	if (p_map->map[y][x] == 'W')
		p_map->player.rot_angle = M_PI;
	if (p_map->map[y][x] == 'E')
		p_map->player.rot_angle = 0;
	p_map->player.y_double = y * TILE_SIZE + TILE_SIZE / 2.0;
	p_map->player.x_double = x * TILE_SIZE + TILE_SIZE / 2.0;
	p_map->player.walk_dir = 0;
	p_map->player.walk_side = 0;
	p_map->player.turn_dir = 0;
	p_map->p_sz = (TILE_SIZE / 3);
	p_map->player.walk_speed = p_map->p_sz;
	if (p_map->player.walk_speed > TILE_SIZE)
		p_map->player.walk_speed = 5;
	p_map->player.turn_speed = 6 * (M_PI / 180);
	p_map->x_inter = -1;
	p_map->y_inter = -1;
	p_map->door.is_open = 0;
	p_map->door.tmp_is_open = 0;
	p_map->door.inside_door = 0;
}
