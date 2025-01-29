/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:32 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/29 19:20:45 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "libft/libft.h"
#include "./MLX42/include/MLX42/MLX42.h"

#define BUFFER_SIZE 145

#define WIDTH 1200
#define HEIGHT 1000
#define M_WIDTH (WIDTH / 4)
#define M_HEIGHT (HEIGHT / 4)
#define MOVE_MAP 10
#define FOV 60
#define TILE_SIZE 30
#define DIST_PROJ_PLANE (WIDTH / (2 * tan((FOV * M_PI / 180) / 2)))
#define PLAYER_SIZE (TILE_SIZE / 3)

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player
{
	mlx_image_t	*img;
	int			width;
	int			height;
	double		x_double;
	double		y_double;
	double		rot_angle;
	int			walk_dir;
	int			walk_side;
	int			turn_dir;
	double		walk_speed;
	double		turn_speed;
}	t_player;

typedef struct s_ray
{
	float	angle;
	float	dist;
	double player_x;
    double player_y;
	double x_inter;
	double y_inter;
	double x_step;
	double y_step;
	int facing_down;
	int facing_up;
	int facing_right;
	int facing_left;
}	t_ray;

typedef struct s_dir
{
	float	angle;
	float	dx;
	float	dy;
	float	length;
	float	x_increment;
	float	y_increment;
	int		step_count;
}	t_dir;

typedef struct s_door
{
	int	is_open;
	int	inside_door;
	int	is_dor_v;
	int	is_dor_h;
}	t_door;

typedef struct s_minimap_vars
{
	int	y_top;
	int	y_bottom;
	int	x_right;
	int	x_left;
	int	x_scale;
	int	y_scale;
	int	player_x;
	int	player_y;
}	t_minimap_vars;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int			cell_w;
	int			cell_h;
	int			base_height;
	int			base_width;
}	t_minimap;



typedef struct s_map
{
	char			**map;
	double			x_inter;
	double			y_inter;
	int				fd;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*d;
	double			ray_angle;
	t_color			f;
	t_color			c;
	t_player		player;
	t_door			door;
	t_ray			ray;
	t_minimap		minimap;
	mlx_t			*mlx;
	mlx_image_t		*map_img;
	mlx_texture_t	*textures[5];
	int				map_width;
	int				map_height;
	mlx_image_t		**player_img;
	int 			i;
}	t_map;

char			*get_next_line(int fd);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
int				ft_strchr2( char *s);
char			**my_split(char const *s, char *c);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_free(char **str);
int				parsing_color(char *line, t_map *map, int *counter);
int				process_map_lines(t_map *p_map,
					int status, int is_map, int counter);
int				parsing_texture(char *line, t_map *map, int *counter);
void			check_newline(char *map_oned, t_map *map);
int				ft_count(char **str);
int				is_texture_valid(t_map *map);
int				skip_line_empty(char *line);
char			*skip_space(char *line);
void			init_map(t_map **p_map);
void			free_map(t_map *map);
void			parse_map(t_map *p_map);
int				check_namnf(t_map *p_map, char *av);
void			get_posplayer(t_map *p_map, int i, int j);
void			map_render(t_map *p_map);
void			ft_minimap(t_map *p_map);
int				get_rgba(int r, int g, int b, int a);
int				get_cell_color(t_map *p_map, int x, int y);
void			move_player(t_map *p_map);
void			raycasting(t_map *p_map);
void			draw_minimap(t_map *p_map);
void			_texters(double yp, int *colors,
					mlx_texture_t *texture, t_map *p_map);
mlx_texture_t	*ft_whiche_texture( mlx_texture_t *texture[4],
					double ray_angle, int side);
void			key_release(t_map *p_map);
void			close_win(void *param);
int				hit_wall(t_map *p_map, double x, double y, int key_use);
void			draw_ray_with_angle(float x0, float y0, t_map *p_map);
void			free_map_textures(t_map *map);
int				is_texture_valid(t_map *map);
mlx_image_t		**generating_frames(t_map *map, char *path, int frames);
