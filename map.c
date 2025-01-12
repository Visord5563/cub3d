/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:37 by relamine          #+#    #+#             */
/*   Updated: 2025/01/11 02:15:47 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_render(t_map *p_map)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	p_map->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!p_map->mlx)
	{
		printf("Error\n");
		free_map(p_map);
		exit(1);
	}
	p_map->map_img = mlx_new_image(p_map->mlx, WIDTH, HEIGHT);
	if (!p_map->map_img
		|| (mlx_image_to_window(p_map->mlx, p_map->map_img, 0, 0) < 0))
	{
		printf("Error\n");
		free_map(p_map);
		exit(1);
	}
	ft_minimap(p_map);
	raycasting(p_map);
	move_player(p_map);
	mlx_loop(p_map->mlx);
}
