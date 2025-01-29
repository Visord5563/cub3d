/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:41:29 by relamine          #+#    #+#             */
/*   Updated: 2025/01/29 21:31:13 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	while (st1[i] != '\0' && st2[i] != '\0' && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}

int	ft_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	skip_line_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\v'
			&& *line != '\f' && *line != '\r' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

char	*skip_space(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\v'
		|| *line == '\f' || *line == '\r')
		line++;
	return (line);
}

void load_tex(t_map *map , mlx_image_t **new, char *tx_path, int i)
{
	mlx_texture_t	*tx;

	tx = mlx_load_png(tx_path);
	new[i] = mlx_texture_to_image(map->mlx, tx);
	new[i]->enabled = (i == 0);
	mlx_resize_image(new[i], WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, new[i], 0, 0);
	mlx_delete_texture(tx);
}

mlx_image_t	**generating_frames(t_map *map, char *path, int frames)
{
	mlx_image_t		**new;
	char			*tmp;
	char			*tx_path;
	int				i;

	i = 0;
	new = malloc(frames * sizeof(mlx_image_t *));
	if (!new)
		return (NULL);
	while (i < frames)
	{
		tmp = ft_itoa(i + 1);
		tx_path = ft_strjoin(ft_strjoin(ft_strdup(path), tmp), ".png");
		load_tex(map, new, tx_path, i);
		free(tmp);
		free(tx_path);
		i++;
	}
	new[0]->enabled = true;
	return (new);
}

int	is_texture_valid(t_map *map)
{
	map->textures[0] = mlx_load_png(map->no);
	if (!map->textures[0])
		return (0);
	map->textures[1] = mlx_load_png(map->so);
	if (!map->textures[1])
		return (0);
	map->textures[2] = mlx_load_png(map->we);
	if (!map->textures[2])
		return (0);
	map->textures[3] = mlx_load_png(map->ea);
	if (!map->textures[3])
		return (0);
	return (1);
}
