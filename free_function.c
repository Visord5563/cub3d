/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:22:09 by relamine          #+#    #+#             */
/*   Updated: 2025/01/29 22:10:52 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	delete_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (map->textures[i])
			mlx_delete_texture(map->textures[i]);
		i++;
	}
	i = 0;
	while (i < 30)
	{
		if (map->player_img[i])
			mlx_delete_image(map->mlx, map->player_img[i]);
		i++;
	}
	free(map->player_img);
}

void	free_map_textures(t_map *map)
{
	if (map->no)
	{
		free(map->no);
		map->no = NULL;
	}
	if (map->so)
	{
		free(map->so);
		map->so = NULL;
	}
	if (map->we)
	{
		free(map->we);
		map->we = NULL;
	}
	if (map->ea)
	{
		free(map->ea);
		map->ea = NULL;
	}
	if (map->d)
	{
		free(map->d);
		map->d = NULL;
	}
}

void	free_map(t_map *map)
{
	free_map_textures(map);
	if (map->map)
		ft_free(map->map);
	if (map->fd != -1)
		close(map->fd);
	if (map->map_img)
		mlx_delete_image(map->mlx, map->map_img);
	if (map->minimap.img)
		mlx_delete_image(map->mlx, map->minimap.img);
	if (map->player.img)
		mlx_delete_image(map->mlx, map->player.img);
	if (map->mlx)
		mlx_terminate(map->mlx);
	delete_textures(map);
	free(map);
}
