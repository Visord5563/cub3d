/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:54:27 by relamine          #+#    #+#             */
/*   Updated: 2025/01/20 00:23:29 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_with_angle(float x0, float y0, t_map *p_map)
{
	t_dir	ray;

	ray.angle = fmod(p_map->player.rot_angle, 2 * M_PI);
	if (ray.angle < 0)
		ray.angle += 2 * M_PI;
	ray.dx = cos(ray.angle) * fmax(p_map->player.width, p_map->player.height);
	ray.dy = sin(ray.angle) * fmax(p_map->player.width, p_map->player.height);
	ray.length = fmax(fabs(ray.dx), fabs(ray.dy));
	ray.x_increment = ray.dx / ray.length;
	ray.y_increment = ray.dy / ray.length;
	ray.step_count = 0;
	while (ray.step_count < ray.length)
	{
		mlx_put_pixel(p_map->map_img, round(x0),
			round(y0), get_rgba(255, 69, 0, 255));
		x0 += ray.x_increment;
		y0 += ray.y_increment;
		ray.step_count++;
	}
}

void	create_player(t_map *p_map)
{
	int	x;
	int	y;

	p_map->player.width = p_map->minimap.cell_w / 3;
	p_map->player.height = p_map->minimap.cell_h / 3;
	p_map->player.img = mlx_new_image(p_map->mlx,
			p_map->player.width, p_map->player.height);
	if (!p_map->player.img || mlx_image_to_window(p_map->mlx,
			p_map->player.img, MOVE_MAP, MOVE_MAP) < 0)
	{
		printf("Error\n");
		return (free_map(p_map), exit(1));
	}
	y = 0;
	while (y < p_map->player.height)
	{
		x = 0;
		while (x < p_map->player.width)
		{
			mlx_put_pixel(p_map->player.img, x, y,
				get_rgba(241, 196, 15, 255));
			x++;
		}
		y++;
	}
}

void	ft_minimap(t_map *p_map)
{
	p_map->minimap.img = mlx_new_image(p_map->mlx, M_WIDTH, M_HEIGHT);
	if (!p_map->minimap.img || (mlx_image_to_window(p_map->mlx,
				p_map->minimap.img, MOVE_MAP, MOVE_MAP) < 0))
	{
		printf("Error\n");
		free_map(p_map);
		exit(1);
	}
	p_map->minimap.base_height = (p_map->map_height) / 2;
	p_map->minimap.base_width = (p_map->map_width) / 2;
	p_map->minimap.cell_h = M_HEIGHT / p_map->minimap.base_height;
	p_map->minimap.cell_w = M_WIDTH / p_map->minimap.base_width;
	create_player(p_map);
}
