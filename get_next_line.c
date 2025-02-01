/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:20:06 by saharchi          #+#    #+#             */
/*   Updated: 2025/02/01 21:37:12 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_r(char **s, int j)
{
	char	*s1;

	s1 = ft_substr(*s, j, ft_strlen(*s) - j);
	if (!s1)
		return (NULL);
	free(*s);
	*s = NULL;
	return (s1);
}

char	*get_newline(char **s, int j)
{
	char	*line;

	line = ft_substr(*s, 0, j);
	if (!line)
		return (NULL);
	*s = get_r(s, j);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*string;
	char		*buff;
	int			i;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!string)
		string = ft_strdup("");
	i = read(fd, buff, BUFFER_SIZE);
	while (i >= 0)
	{
		buff[i] = '\0';
		string = ft_strjoin(string, buff);
		if (string[0] == '\0' || !string)
			break ;
		if (ft_strchr2(string) != -1)
			return (free(buff), get_newline(&string, ft_strchr2(string)));
		if (i == 0)
			return (free(buff), get_r(&string, 0));
		i = read(fd, buff, BUFFER_SIZE);
	}
	return (free(buff), free(string), string = NULL, NULL);
}
