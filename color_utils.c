/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 00:47:31 by relamine          #+#    #+#             */
/*   Updated: 2025/01/11 00:51:34 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_cell_color(t_map *p_map, int x, int y)
{
	int	color;

	if (p_map->map[y][x] == '1')
		color = get_rgba(255, 255, 255, 255);
	else
		color = get_rgba(0, 0, 0, 100);
	return (color);
}
