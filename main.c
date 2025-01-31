/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:37 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/31 21:25:25 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_element(char map , t_map *p_map)
{
	if (map != '1' && map != '0' && !is_space(map)
		&& !check_player(map) && map != 'D')
		error(p_map);
	return (1);
}

void	check_newline(char *map_oned, t_map *map)
{
	int	i;
	int	ch;

	i = 0;
	ch = 0;
	while (map_oned[i])
	{
		if (map_oned[i] == '\n' && map_oned[i + 1] == '\n')
			ch = 1;
		if (ch == 1 && map_oned[i] == '1')
		{
			free(map_oned);
			error(map);
		}
		i++;
	}
}

void	leaks(void)
{
	system("leaks cub3D");
}
char	**resize_map(t_map *p_map)
{
	int		i;
	int		j;
	char	**new_map;

	i = -1;
	new_map = malloc(sizeof(char *) * (p_map->map_height + 1));
	if (!new_map)
		error(p_map);
	while (++i < p_map->map_height)
	{
		new_map[i] = malloc(sizeof(char) * (p_map->map_width + 1));
		if (!new_map[i])
			error(p_map);
		j = -1;
		while (++j < p_map->map_width)
		{
			if (j < (int)ft_strlen(p_map->map[i]))
				new_map[i][j] = p_map->map[i][j];
			else
				new_map[i][j] = ' ';
		}
		new_map[i][j] = '\0';
	}
	new_map[i] = NULL;
	return (ft_free(p_map->map), new_map);
}

int	main(int argc, char **argv)
{
	t_map	*p_map;
	int		status;

	// atexit(leaks);
	status = 0;
	init_map(&p_map);
	if (argc != 2 || !ft_strchr(argv[1], '.')
		|| !check_namnf(p_map, argv[1]))
		return (free_map(p_map), 1);
	if (process_map_lines(p_map, 0, 0, 0))
		return (1);
	get_width_height(p_map);
	p_map->map = resize_map(p_map);
	parse_map(p_map);
	map_render(p_map);
	free_map_textures(p_map);
}
