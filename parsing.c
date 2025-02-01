/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:09:38 by relamine          #+#    #+#             */
/*   Updated: 2025/02/01 21:37:49 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_map_oned(char *map_oned, t_map *p_map, int counter)
{
	if (!map_oned || counter != 6)
		return (printf("Error\n"), free_map(p_map), 1);
	else
	{
		close(p_map->fd);
		p_map->fd = -1;
	}
	check_newline(map_oned, p_map);
	p_map->map = ft_split(map_oned, '\n');
	if (!p_map->map)
		return (printf("Error\n"), free(map_oned), free_map(p_map), 1);
	free(map_oned);
	return (0);
}

void	append_line_to_map(char **map_oned,
			char **line, t_map *p_map, int *is_map)
{
	*map_oned = ft_strjoin(*map_oned, *line);
	if (!(*map_oned))
	{
		free(*line);
		error(p_map);
	}
	free(*line);
	*line = get_next_line(p_map->fd);
	*is_map = 1;
}

int	handle_empty_line(char **line, int is_map, t_map *p_map)
{
	if (!is_map && skip_line_empty(*line))
	{
		free(*line);
		*line = get_next_line(p_map->fd);
		return (1);
	}
	return (0);
}

int	process_map_lines(t_map *p_map, int status, int is_map, int counter)
{
	char	*line;
	char	*map_oned;

	line = get_next_line(p_map->fd);
	map_oned = NULL;
	while (line)
	{
		if (handle_empty_line(&line, is_map, p_map))
			continue ;
		status = parsing_color(line, p_map, &counter);
		if (status == 2)
		{
			status = parsing_texture(line, p_map, &counter);
			if (status == 2)
			{
				append_line_to_map(&map_oned, &line, p_map, &is_map);
				continue ;
			}
		}
		free(line);
		if (status == 0)
			return (printf("Error\n"), free_map(p_map), 1);
		line = get_next_line(p_map->fd);
	}
	return (process_map_oned(map_oned, p_map, counter));
}
