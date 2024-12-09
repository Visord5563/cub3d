/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:37 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/09 07:05:06 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void f()
{
	system("leaks cub3D");
}


int main(int argc, char **argv)
{
	t_map	*p_map;
	int		status;
	int		i;
	int		counter;
	char	*line;
	char	*map_oned;
	char	**map;
	int		is_map;

	i = 1;
	counter = 0;
	map_oned = NULL;
	map = NULL;
	is_map = 0;
	init_map(&p_map);
    if (argc != 2 || !check_namnf(p_map, argv[1]))
        return (free_map(p_map), 1);
	// atexit(f);
	while ((line = get_next_line(p_map->fd)))
	{
		if (skip_line_empty(line) && !is_map)
		{
			free(line);
			continue;
		}
		status = parsing_color(line, p_map);
		if (status == 0)
			return (printf("Error\n"), free(line), free_map(p_map), 1);
		else if (status == 2)
		{
			status = parsing_texture(line, p_map, counter);
			if (status == 2)
			{
				if (counter != 6 || !is_texture_valid(p_map))
					return (printf("*Error\n"), free(line), free_map(p_map), 1);
				map_oned = ft_strjoin(map_oned, line);
				if (!map_oned)
					return (printf("Error\n"), free(line), free_map(p_map), 1);
				free(line);
				is_map = 1;
				continue;
			}
			else if (status == 0)
				return (printf("*=Error\n"), free(line), free_map(p_map), 1);
		}
		counter++;
		free(line);
	}

	if (counter != 6 || !is_texture_valid(p_map))
		return (printf("Error\n"), free_map(p_map), 1);

	map = ft_split(map_oned, '\n');
	if (!map)
		return (printf("Error\n"), free(map_oned), free_map(p_map), 1);
	free(map_oned);
	parse_map(p_map, map);
}



