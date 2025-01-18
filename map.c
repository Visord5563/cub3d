/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:37 by relamine          #+#    #+#             */
/*   Updated: 2025/01/18 09:41:30 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_width_height(t_map *p_map)
{
	int	i;
	int	j;
	int	max;
	int	len;

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
	p_map->map_width = max;
	p_map->map_height = i;
}

void	ft_realloc(t_map *map)
{
	int		y;
	int		x;
	char	**tmp;

	y = 0;
	tmp = malloc(sizeof(char *) * ((map->map_height) + 1));
	while (y < map->map_height)
	{
		tmp[y] = malloc(sizeof(char) * (map->map_width));
		if (!tmp[y])
			return (printf("Error\n"), ft_free(tmp), free_map(map), exit(1));
		x = 0;
		while (x < map->map_width)
		{
			if (x < (int)ft_strlen(map->map[y]))
				tmp[y][x] = map->map[y][x];
			else
				tmp[y][x] = ' ';
			x++;
		}
		y++;
	}
	tmp[y] = NULL;
	ft_free(map->map);
	map->map = tmp;
}

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
	get_width_height(p_map);
	ft_realloc(p_map);
	ft_minimap(p_map);
	raycasting(p_map);
	move_player(p_map);
	mlx_loop(p_map->mlx);
}
