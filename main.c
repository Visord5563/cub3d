/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:37 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/18 12:12:51 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			printf("Error\n");
			free(map_oned);
			free_map(map);
			exit(1);
		}
		i++;
	}
}

void	leaks(void)
{
	system("leaks cub3D");
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
	parse_map(p_map);
	map_render(p_map);
}
