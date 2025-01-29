/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:35:21 by saharchi          #+#    #+#             */
/*   Updated: 2025/01/29 22:36:23 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_map *p_map, double ray_angle)
{
	p_map->ray.facing_down = 0;
	p_map->ray.facing_up = 0;
	p_map->ray.facing_right = 0;
	p_map->ray.facing_left = 0;
	p_map->ray.player_x = p_map->player.x_double;
	p_map->ray.player_y = p_map->player.y_double;
	p_map->ray.x_step = 0;
	p_map->ray.y_step = 0;
	if (ray_angle > 0 && ray_angle < M_PI)
		p_map->ray.facing_down = 1;
	if (!p_map->ray.facing_down)
		p_map->ray.facing_up = 1;
	if (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI)
		p_map->ray.facing_right = 1;
	if (!p_map->ray.facing_right)
		p_map->ray.facing_left = 1;
}

void	get_y(t_map *p_map, double ray_angle)
{
	double	player_x;
	double	player_y;

	player_x = p_map->ray.player_x;
	player_y = p_map->ray.player_y;
	p_map->ray.y_step = TILE_SIZE;
	if (p_map->ray.facing_up)
		p_map->ray.y_step *= -1;
	p_map->ray.x_step = TILE_SIZE / tan(ray_angle);
	if (p_map->ray.facing_left && p_map->ray.x_step > 0)
		p_map->ray.x_step *= -1;	
	if (p_map->ray.facing_right && p_map->ray.x_step < 0)
		p_map->ray.x_step *= -1;
	p_map->ray.y_inter = floor(player_y / TILE_SIZE) * TILE_SIZE;
	if (p_map->ray.facing_down)
		p_map->ray.y_inter += TILE_SIZE;
	p_map->ray.x_inter = player_x
		+ (p_map->ray.y_inter - player_y) / tan(ray_angle);
}

void	get_x(t_map *p_map, double ray_angle)
{
	double	player_x;
	double	player_y;

	player_x = p_map->ray.player_x;
	player_y = p_map->ray.player_y;
	p_map->ray.x_step = TILE_SIZE;
	if (p_map->ray.facing_left)
		p_map->ray.x_step *= -1;
	p_map->ray.y_step = TILE_SIZE * tan(ray_angle);
	if (p_map->ray.facing_up && p_map->ray.y_step > 0)
		p_map->ray.y_step *= -1;
	if (p_map->ray.facing_down && p_map->ray.y_step < 0)
		p_map->ray.y_step *= -1;
	p_map->ray.x_inter = floor(player_x / TILE_SIZE) * TILE_SIZE;
	if (p_map->ray.facing_right)
		p_map->ray.x_inter += TILE_SIZE;
	p_map->ray.y_inter = player_y
		+ (p_map->ray.x_inter - player_x) * tan(ray_angle);
}


int	check_boundaries(t_map *p_map, int map_x, int map_y)
{
	if (map_y < 0 || map_x < 0 || map_y >= p_map->map_height
		|| map_x >= p_map->map_width)
		return (1);
	return (0);
}

double	calculate_distance(t_map *p_map)
{
	return (sqrt(pow(p_map->ray.x_inter - p_map->ray.player_x, 2)
			+ pow(p_map->ray.y_inter - p_map->ray.player_y, 2)));
}

int	check_wall_h(t_map *p_map, int map_x, int map_y)
{
	if (p_map->map[map_y][map_x] == '1' || p_map->map[map_y][map_x] == 'D')
	{
		if (p_map->map[map_y][map_x] == 'D')
			p_map->door.is_dor_h = 1;
		p_map->x_inter = p_map->ray.x_inter;
		return (1);
	}
	return (0);
}

double	get_horizontal(t_map *p_map, double ray_angle)
{
	int	map_x;
	int	map_y;

	init_ray(p_map, ray_angle);
	get_y(p_map, ray_angle);
	while (p_map->ray.x_inter >= 0
		&& p_map->ray.x_inter < (p_map->map_width * TILE_SIZE)
		&& p_map->ray.y_inter >= 0
		&& p_map->ray.y_inter < (p_map->map_height * TILE_SIZE))
	{
		map_x = floor(p_map->ray.x_inter / TILE_SIZE);
		map_y = floor(p_map->ray.y_inter / TILE_SIZE);
		if (p_map->ray.facing_up)
			map_y -= 1;
		if (check_boundaries(p_map, map_x, map_y))
			return (-1);
		if (check_wall_h(p_map, map_x, map_y))
			return (calculate_distance(p_map));
		p_map->ray.x_inter += p_map->ray.x_step;
		p_map->ray.y_inter += p_map->ray.y_step;
	}
	return (-1);
}

int	check_wall_v(t_map *p_map, int map_x, int map_y)
{
	if (p_map->map[map_y][map_x] == '1' || p_map->map[map_y][map_x] == 'D')
	{
		if (p_map->map[map_y][map_x] == 'D')
			p_map->door.is_dor_v = 1;
		p_map->y_inter = p_map->ray.y_inter;
		return (1);
	}
	return (0);
}

double	get_vertical(t_map *p_map, double ray_angle)
{
	int	map_x;
	int	map_y;

	init_ray(p_map, ray_angle);
	get_x(p_map, ray_angle);
	while (p_map->ray.x_inter >= 0
		&& p_map->ray.x_inter < (p_map->map_width * TILE_SIZE)
		&& p_map->ray.y_inter >= 0
		&& p_map->ray.y_inter < (p_map->map_height * TILE_SIZE))
	{
		map_x = floor(p_map->ray.x_inter / TILE_SIZE);
		if (p_map->ray.facing_left)
			map_x -= 1;
		map_y = floor(p_map->ray.y_inter / TILE_SIZE);
		if (check_boundaries(p_map, map_x, map_y))
			return (-1);
		if (check_wall_v(p_map, map_x, map_y))
			return (calculate_distance(p_map));
		p_map->ray.x_inter += p_map->ray.x_step;
		p_map->ray.y_inter += p_map->ray.y_step;
	}
	return (-1);
}

void	get_wall(double distance, double *wall_height, double *wall_top, double *wall_bottom)
{
	*wall_height = (TILE_SIZE * DIST_PROJ_PLANE) / distance;
	*wall_top = (HEIGHT / 2) - (*wall_height / 2);
	*wall_bottom = *wall_top + *wall_height;
	if (*wall_top < 0)
		*wall_top = 0;
}

void	draw_wall_section(t_map *p_map, int i, int y, int color[4])
{
	mlx_put_pixel(p_map->map_img, i, y,
		get_rgba(color[0], color[1], color[2], color[3]));
}

void	draw_floor_ceiling(t_map *p_map, int i, int y)
{
	if (y > (HEIGHT / 2))
		mlx_put_pixel(p_map->map_img, i, y,
			get_rgba(p_map->c.r, p_map->c.g, p_map->c.b, 255));
	else
		mlx_put_pixel(p_map->map_img, i, y,
			get_rgba(p_map->f.r, p_map->f.g, p_map->f.b, 255));
}

void	render_wall_texture(t_map *p_map, double distance, int i, mlx_texture_t *texture)
{
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	int		y;
	int		color[4];

	get_wall(distance, &wall_height, &wall_top, &wall_bottom);
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= wall_top && y <= wall_bottom && y < HEIGHT)
		{
			_texters(1.0 - (wall_bottom - y) / wall_height, color,
				texture, p_map);
			draw_wall_section(p_map, i, y, color);
		}
		else
			draw_floor_ceiling(p_map, i, y);
		y++;
	}
}

mlx_texture_t	*choose_texture(t_map *p_map, int side, double *distance)
{
	mlx_texture_t	*texture;

	texture = ft_whiche_texture(p_map->textures, p_map->ray_angle, side);
	if (p_map->door.is_dor_v || p_map->door.is_dor_h)
		texture = p_map->textures[4];
	*distance *= cos(p_map->ray_angle - p_map->player.rot_angle);

	return (texture);
}

void	rander_texter(t_map *p_map, double distance, int i, int side)
{
	mlx_texture_t	*texture;

	texture = choose_texture(p_map, side, &distance);
	render_wall_texture(p_map, distance, i, texture);
}


void	check_ray(t_map *p_map, double *distance, int *side)
{
	double	distance_h;
	double	distance_v;

	p_map->door.is_dor_h = 0;
	p_map->door.is_dor_v = 0;
	p_map->ray_angle = fmod(p_map->ray_angle, 2 * M_PI);
	if (p_map->ray_angle < 0)
		p_map->ray_angle += 2 * M_PI;
	distance_h = get_horizontal(p_map, p_map->ray_angle);
	distance_v = get_vertical(p_map, p_map->ray_angle);
	if (distance_h != -1 && (distance_v == -1 || distance_h < distance_v))
	{
		p_map->y_inter = -1;
		*distance = distance_h;
		*side = 1;
		p_map->door.is_dor_v = 0;
	}
	else
	{
		p_map->x_inter = -1;
		*distance = distance_v;
		p_map->door.is_dor_h = 0;
	}
}

void	raycasting(t_map *p_map)
{
	double	distance;
	double	angle_increment ;
	int		i;
	int		side;

	i = 0;
	distance = 0;
	angle_increment = FOV * (M_PI / 180) / WIDTH;
	p_map->ray_angle = p_map->player.rot_angle - (FOV * (M_PI / 180) / 2);
	while (i < WIDTH)
	{
		side = 0;
		check_ray(p_map, &distance, &side);
		rander_texter(p_map, distance, i, side);
		p_map->ray_angle += angle_increment;
		i++;
	}
	draw_minimap(p_map);
}
