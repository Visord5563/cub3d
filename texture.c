/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:32:06 by relamine          #+#    #+#             */
/*   Updated: 2025/01/19 19:51:49 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	_texters(double yp, int *colors, mlx_texture_t	*texture, t_map *p_map)
{
	double	pos;
	int		x;
	int		y;
	int		pixel_index;

	if (p_map->x_inter != -1)
		pos = fmod(p_map->x_inter, TILE_SIZE) / TILE_SIZE;
	else
		pos = fmod(p_map->y_inter, TILE_SIZE) / TILE_SIZE;
	x = (int)(pos * texture->width);
	y = (int)(yp * texture->height);
	if (x == (int)texture->width)
		x = texture->width - 1;
	if (y == (int)texture->height)
		y = texture->height - 1;
	pixel_index = (y * texture->width + x) * texture->bytes_per_pixel;
	colors[0] = texture->pixels[pixel_index];
	colors[1] = texture->pixels[pixel_index + 1];
	colors[2] = texture->pixels[pixel_index + 2];
	colors[3] = texture->pixels[pixel_index + 3];
}

mlx_texture_t	*ft_whiche_texture( mlx_texture_t *texture[5],
	double ray_angle, int side)
{
	if (ray_angle > 0 && ray_angle < M_PI && side == 1)
		return (texture[0]);
	else if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2 && side == 0)
		return (texture[1]);
	else if (ray_angle > M_PI && ray_angle < 2 * M_PI && side == 1)
		return (texture[2]);
	return (texture[3]);
}
