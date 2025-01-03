/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:37 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/01 16:35:12 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void f()
{
	system("leaks cub3D");
}

void check_newline(char *map_oned, t_map *map)
{
	int i = 0;
	int ch = 0;
	while(map_oned[i])
	{
		if (map_oned[i] == '\n' && map_oned[i+1] == '\n')
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
void get_width_height(t_map *p_map)
{
	int i;
	int j;
	int max;
	int len;

	i = 0;
	max = 0;
	len = ft_count(p_map->map);
	while (i < len)
	{
		j = 0;
		while (p_map->map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	p_map->map_width = max;
	p_map->map_height = i;
}
void leaks(void)
{
	system("leaks cub3D");
}

void ft_realloc(t_map *map)
{
	int y;
	int x;
	char **tmp;

	y = 0;
	tmp = malloc(sizeof(char *) * ((map->map_height) + 1));
	while (y < map->map_height)
	{
		tmp[y] = malloc(sizeof(char) * (map->map_width));
		if (!tmp[y])
		{
			printf("Error\n");
			ft_free(tmp);
			free_map(map);
			exit(1);
		}
		x = 0;
		while (x < map->map_width)
		{
			if (x < (int)ft_strlen(map->map[y]))
				tmp[y][x] = map->map[y][x];
			else
				tmp[y][x] = ' ';
			x++;
		}
		y++;
	}
	tmp[y] = NULL;
	ft_free(map->map);
	map->map = tmp;
}

int main(int argc, char **argv)
{
	t_map	*p_map;
	int		status;
	// int		i;
	int		counter;
	char	*line;
	char	*map_oned;
	// char	**map;
	int		is_map;

	// i = 1;
	// atexit(leaks);
	counter = 0;
	map_oned = NULL;
	// map = NULL;
	is_map = 0;
	init_map(&p_map);
    if (argc != 2 || !ft_strchr(argv[1], '.') || !check_namnf(p_map, argv[1]))
	{
        return (free_map(p_map), 1);
	}
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
				if (counter != 6)
					return (printf("Error\n"), free(line), free_map(p_map), 1);
				map_oned = ft_strjoin(map_oned, line);
				if (!map_oned)
					return (printf("Error\n"), free(line), free_map(p_map), 1);
				free(line);
				is_map = 1;
				continue;
			}
			else if (status == 0)
				return (printf("Error\n"), free(line), free_map(p_map), 1);
		}
		counter++;
		free(line);
	}
	if ( !map_oned || counter != 6)
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
	parse_map(p_map);
	get_width_height(p_map);
	ft_realloc(p_map);
	
	map_render(p_map);
}



