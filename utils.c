/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:01:42 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/31 20:02:36 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(t_map *p_map)
{
	printf("Error\n");
	free_map(p_map);
	exit(1);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

void	check_wall(t_map *p_map, char *map)
{
	int	j;

	j = 0;
	while (map[j])
	{
		if (map[j] != '1' && !is_space(map[j]))
			error(p_map);
		j++;
	}
}

int	check_space(char **map, int i, int j)
{
	if (is_space(map[i][j + 1]) || is_space(map[i][j - 1])
		|| is_space(map[i - 1][j]) || is_space(map[i + 1][j]))
		return (1);
	return (0);
}

int	check_player(char map)
{
	if (map == 'N' || map == 'S' || map == 'W' || map == 'E')
		return (1);
	return (0);
}