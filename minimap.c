/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:54:27 by relamine          #+#    #+#             */
/*   Updated: 2024/12/10 07:23:00 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define WIDTH 256
#define HEIGHT 256


void minimap(t_map *p_map)
{
	(void)p_map;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		printf("Error\n"), exit(1);

	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		printf("Error\n"), exit(1);

	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	mlx_loop(mlx);
	mlx_terminate(mlx);
}