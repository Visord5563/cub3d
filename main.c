/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:37 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/08 22:39:03 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_namnf(t_map *p_map, char *av)
{
    if(ft_strlen(ft_strchr(av, '.')) == 4 && !ft_strcmp(strchr(av, '.'), ".cub"))
    {
		p_map->fd = open(av  , O_RDONLY);
		if (p_map->fd == -1) 
		{
	        printf("Error Number % d\n", errno);
        	perror("Program");
			free(p_map);
			exit(1);
    	}
		return 1;
    }
	return 0;
}

int ft_count(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int parse_map(t_map *p_map, char **map)
{
	int i = 0;
	int j = 0;
	int c ;
	char *check;
	while(map[0][j])
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
		{
			printf("error\n");
			exit(1);
		}
		j++;
	}
	i = 1;
	c = ft_count(map);
	int cou = 0;
	while(map[i] && i < c - 1)
	{
		j = 0;
		while(map[i][j] == ' ')
			j++;
		if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
		{
			cou++;
			if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || j >= (int)ft_strlen(map[i - 1]) || j >= (int)ft_strlen(map[i + 1]))
			{
				printf("error\n");
				exit(1);
			}
		}
		check = ft_strtrim(map[i], " \t\v\f\r\n");
		if (check[0] != '1' || check[ft_strlen(check) - 1] != '1')
		{
			printf("error\n");
			exit(1);
		}
		while(map[i][j])
		{
			// printf("(%c)--(%d)--(%d)--(%d)\n",map[i][j], j, (int)ft_strlen(map[i - 1]), (int)ft_strlen(map[i + 1]));
			if (map[i][j] == '0' && (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || j >= (int)ft_strlen(map[i - 1]) || j >= (int)ft_strlen(map[i + 1])))
			{
				printf("error\n");
				exit(1);
			}
			j++;
		}
		// printf("-----------------------\n%d\n", i);
		// printf("-----------------------\n");
		i++;
	}
	j = 0;
	while(map[c - 1][j])
	{
		if (map[c - 1][j] != '1' && map[c - 1][j] != ' ')
		{
			printf("error\n");
			exit(1);
		}
		j++;
	}
	if (cou != 1)
	{
		printf("error\n");
		exit(1);
	}
	p_map->map = map;
	return 0;
}

int main(int ac, char **av)
{
	t_map *p_map;

	p_map = malloc(sizeof(t_map));
    if (ac != 2 || !check_namnf(p_map, av[1]))
        return 1;
	 char *s;
	 char *j = ft_strdup("");
	 char **map;
    while((s = get_next_line(p_map->fd))){
        j = ft_strjoin(j, s);
    }
	map = ft_split(j, '\n');
	parse_map(p_map, map);
	return 0;
}