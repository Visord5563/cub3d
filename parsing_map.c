/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:47:41 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/31 21:21:54 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_and_exit(char **line, int i, int j, t_map *p_map)
{
	if (check_space(line, i, j))
		error(p_map);
	if (!p_map->d)
		error(p_map);
}

void	check_player_position(char **line, int i, int j, t_map *p_map, int *cou)
{
	(*cou)++;
	check_and_exit(line, i, j, p_map);
	get_posplayer(p_map, i, j);
}

void	check_d_position(char **line, int i, int j, t_map *p_map)
{
	check_and_exit(line, i, j, p_map);
	if ((line[i][j + 1] == '1' && line[i][j - 1] == '1')
		|| (line[i - 1][j] == '1' && line[i + 1][j] == '1'))
	{
		if (line[i][j + 1] == '1' && line[i][j - 1] == '1'
			&& (line[i - 1][j] == '1' || line[i + 1][j] == '1'))
			error(p_map);
		if (line[i - 1][j] == '1' && line[i + 1][j] == '1'
			&& (line[i][j - 1] == '1' || line[i][j + 1] == '1'))
			error(p_map);
	}
	else
		error(p_map);
}

void	valid_line(char **line, int i, t_map *p_map, int *cou)
{
	int	j;

	j = 0;
	while (is_space(line[i][j]))
		j++;
	while (line[i][j] && valid_element(line[i][j], p_map))
	{
		if (check_player(line[i][j]))
			check_player_position(line, i, j, p_map, cou);
		else if (line[i][j] == '0')
			check_and_exit(line, i, j, p_map);
		else if (line[i][j] == 'D')
			check_d_position(line, i, j, p_map);
		j++;
	}
}

void	parse_map(t_map *p_map)
{
	char	*check;
	int		i;
	int		cou;

	i = 0;
	cou = 0;
	check_wall(p_map, p_map->map[0]);
	check_wall(p_map, p_map->map[ft_count(p_map->map) - 1]);
	while (p_map->map[i])
	{
		check = ft_strtrim(p_map->map[i], " \t\v\f\r\n");
		if (check[0] != '1' || check[ft_strlen(check) - 1] != '1')
		{
			free(check);
			error(p_map);
		}
		valid_line(p_map->map, i, p_map, &cou);
		free(check);
		i++;
	}
	if (cou != 1)
		error(p_map);
}
