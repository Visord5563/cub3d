/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:32:55 by relamine          #+#    #+#             */
/*   Updated: 2025/01/19 13:03:53 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_value(char *line, char **texture, char **texture_path, int argc)
{
	char	*sub;
	char	*tmp;
	size_t	len;

	if (*texture_path)
		return (0);
	if (argc >= 3)
	{
		tmp = ft_strnstr(line, texture[0], ft_strlen(line));
		if (!tmp)
			return (0);
		len = ft_strlen(texture[0]);
		sub = ft_substr(tmp, len, ft_strlen(tmp) - len);
		*texture_path = ft_strtrim(sub, " \t\v\f\r\n");
		if (!*texture_path)
			return (free(sub), 0);
		free(sub);
		return (1);
	}
	*texture_path = ft_strdup(texture[1]);
	if (!*texture_path)
		return (0);
	return (1);
}

int	validate_parse_texture(t_map *map, char	**texture, int status, int *counter)
{
	int	is_valid;

	if (!status)
		return (ft_free(texture), 0);
	else if (map->no && map->so && map->we && map->ea)
	{
		is_valid = is_texture_valid(map);
		if (is_valid)
			(*counter) += 4;
		return (ft_free(texture), is_valid);
	}
	return (ft_free(texture), 1);
}

int	handling_door(char *line, char **texture, t_map *map, int argc)
{
	int	status;

	status = get_value(line, texture, &map->d, argc);
	if (!status)
		return (0);
	map->textures[4] = mlx_load_png(map->d);
	if (!map->textures[4])
		return (0);
	return (1);
}

int	handle_texture(char *line, char **texture, t_map *map, int argc)
{
	int	status;

	status = 0;
	if (argc >= 2 && !ft_strcmp(texture[0], "NO"))
		status = get_value(line, texture, &map->no, argc);
	else if (argc >= 2 && !ft_strcmp(texture[0], "SO"))
		status = get_value(line, texture, &map->so, argc);
	else if (argc >= 2 && !ft_strcmp(texture[0], "WE"))
		status = get_value(line, texture, &map->we, argc);
	else if (argc >= 2 && !ft_strcmp(texture[0], "EA"))
		status = get_value(line, texture, &map->ea, argc);
	else if (argc >= 2 && !ft_strcmp(texture[0], "D"))
		status = handling_door(line, texture, map, argc);
	return (status);
}

int	parsing_texture(char *line, t_map *map, int *counter)
{
	char	**texture;
	int		status;
	int		argc;

	status = 0;
	texture = my_split(line, "\t\v\f\r\n ");
	if (!texture)
		return (0);
	argc = ft_count(texture);
	if (*counter == 6)
	{
		if (argc >= 2 && !ft_strcmp(texture[0], "D"))
		{
			status = handling_door(line, texture, map, argc);
			return (ft_free(texture), status);
		}
		return (ft_free(texture), 2);
	}
	status = handle_texture(line, texture, map, argc);
	return (validate_parse_texture(map, texture, status, counter));
}
