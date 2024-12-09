/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:32 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/09 03:17:04 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
//------------
#include <string.h>
# include <limits.h>
//------------

# include "libft/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 145
#endif

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_map
{
    char **map;
    int fd;
	char *no;
	char *so;
	char *we;
	char *ea;
	t_color f;
	t_color c;
} t_map;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strchr2( char *s);
// char	**ft_split(char *s, char c);
// char	*ft_substr(char *s, unsigned int start, size_t len);


// part parsing

char	**my_split(char const *s, char *c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_free(char **str);
int		parsing_color(char *line, t_map *map);
int		parsing_texture(char *line, t_map *map, int counter);
int		ft_count(char **str);
int		is_texture_valid(t_map *map);
int		skip_line_empty(char *line);
char	*skip_space(char *line);
void	init_map(t_map **p_map);
void	free_map(t_map *map);
int		parse_map(t_map *p_map, char **map);
int		check_namnf(t_map *p_map, char *av);


