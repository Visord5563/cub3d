/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:37 by relamine          #+#    #+#             */
/*   Updated: 2025/01/01 08:34:02 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void get_width_height(t_map *p_map)
{
	int i;
	int j;
	int max;
	int len;

	i = 0;
	max = 0;
	len = ft_count(p_map->map);
	while (i < len)
	{
		j = 0;
		while (p_map->map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	p_map->map_width = max * TILE_SIZE;
	p_map->map_height = i * TILE_SIZE;
}

void map_render(t_map *p_map)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	p_map->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!p_map->mlx)
		printf("Error\n"), exit(1);

	p_map->map_img = mlx_new_image(p_map->mlx, WIDTH, HEIGHT);
	if (!p_map->map_img || (mlx_image_to_window(p_map->mlx, p_map->map_img, 0, 0) < 0))
		printf("-Error\n"), exit(1);
	ft_memset(p_map->map_img->pixels, 100, p_map->map_img->width * p_map->map_img->height * sizeof(int32_t));
	get_width_height(p_map);
	// minimap(p_map, p_map->mlx);
	raycasting(p_map);
	move_player(p_map);
	mlx_loop(p_map->mlx);
}

