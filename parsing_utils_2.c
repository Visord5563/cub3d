/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:04:36 by relamine          #+#    #+#             */
/*   Updated: 2025/01/11 00:57:52 by relamine         ###   ########.fr       */
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
	map->map = NULL;
	map->map_img = NULL;
	map->minimap = NULL;
	map->mlx = NULL;
	map->player.player = NULL;
	map->fd = -1;
	init_textures(map);
	*p_map = map;
}

void	delete_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->textures[i])
			mlx_delete_texture(map->textures[i]);
		i++;
	}
}

void	free_map(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->map)
		ft_free(map->map);
	if (map->fd != -1)
		close(map->fd);
	if (map->map_img)
		mlx_delete_image(map->mlx, map->map_img);
	if (map->player.player)
		mlx_delete_image(map->mlx, map->player.player);
	if (map->mlx)
		mlx_terminate(map->mlx);
	delete_textures(map);
	free(map);
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
	p_map->player.walk_speed = 6.0;
	p_map->player.turn_speed = 6 * (M_PI / 180);
	p_map->x_inter = -1;
	p_map->y_inter = -1;
}
