/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:32:06 by relamine          #+#    #+#             */
/*   Updated: 2025/02/01 23:29:54 by saharchi         ###   ########.fr       */
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

void	load_tex(t_map *map, mlx_image_t **new, char *tx_path, int i)
{
	mlx_texture_t	*tx;

	tx = mlx_load_png(tx_path);
	if (!tx)
		error(map);
	new[i] = mlx_texture_to_image(map->mlx, tx);
	new[i]->enabled = (i == 0);
	mlx_resize_image(new[i], WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, new[i], 0, 0);
	mlx_delete_texture(tx);
}

mlx_image_t	**generating_frames(t_map *map, char *path, int frames)
{
	mlx_image_t		**new;
	char			*tx_path;
	int				i;

	i = 0;
	new = malloc(frames * sizeof(mlx_image_t *));
	if (!new)
		error(map);
	while (i < frames)
	{
		tx_path = get_path(path, i);
		if (!tx_path)
		{
			free(new);
			free(path);
			error(map);
		}
		load_tex(map, new, tx_path, i);
		free(tx_path);
		i++;
	}
	new[0]->enabled = true;
	return (new);
}

int	check_namnf(t_map *p_map, char *av)
{
	if (ft_strlen(ft_strchr(av, '.')) == 4
		&& !ft_strcmp(ft_strchr(av, '.'), ".cub"))
	{
		p_map->fd = open(av, O_RDONLY);
		if (p_map->fd == -1)
		{
			printf("Error Number % d\n", errno);
			perror("Program");
			return (0);
		}
		return (1);
	}
	return (0);
}
