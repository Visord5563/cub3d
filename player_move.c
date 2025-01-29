/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:55:56 by relamine          #+#    #+#             */
/*   Updated: 2025/01/29 21:36:23 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_player_f(t_map *p_map)
{
	int	map_x_start;
	int	map_y_start;
	int	map_x_end;
	int	map_y_end;
	int	j;
	
	map_x_start = floor((p_map->player.x_double - floor(PLAYER_SIZE / 2)) / TILE_SIZE);
	map_y_start = floor((p_map->player.y_double - floor(PLAYER_SIZE / 2)) / TILE_SIZE);
	map_x_end = floor((p_map->player.x_double + floor(PLAYER_SIZE / 2)) / TILE_SIZE);
	map_y_end = floor((p_map->player.y_double + floor(PLAYER_SIZE / 2)) / TILE_SIZE);

	while (map_x_start <= map_x_end)
	{
		j = map_y_start;
		while (j <= map_y_end)
		{
			if (j < 0 || map_x_start < 0
				|| j >= p_map->map_height || map_x_start >= p_map->map_width)
				return (1);
			if (p_map->map[j][map_x_start] == 'O')
				return (1);
			j++;
		}
		map_x_start++;
	}
	return (0);
}

int	check_key(mlx_key_data_t keydata, t_map *p_map)
{
	if (keydata.action != MLX_REPEAT && keydata.action != MLX_PRESS)
		return (0);
	if (keydata.key == MLX_KEY_F)
	{
		if (check_player_f(p_map))
			return (0);
		p_map->door.tmp_is_open = p_map->door.is_open;
		if (p_map->map[(int)(p_map->player.y_double / TILE_SIZE)][(int)(p_map->player.x_double / TILE_SIZE)] == 'O')
			return (0);
		if (p_map->door.is_open)
			p_map->door.is_open = 0;
		else
			p_map->door.is_open = 1;
		p_map->player.walk_dir = 1;
		return (2);
	}
	else if (keydata.key == MLX_KEY_W)
		p_map->player.walk_dir = 1;
	else if (keydata.key == MLX_KEY_S)
		p_map->player.walk_dir = -1;
	else if (keydata.key == MLX_KEY_D)
		p_map->player.walk_side = 1;
	else if (keydata.key == MLX_KEY_A)
		p_map->player.walk_side = -1;
	else if (keydata.key == MLX_KEY_LEFT)
		p_map->player.turn_dir = -1;
	else if (keydata.key == MLX_KEY_RIGHT)
		p_map->player.turn_dir = 1;
	else if (keydata.key == MLX_KEY_ESCAPE)
		close_win(p_map);
	else
		return (0);
	return (1);
}

void	update_player_position(t_map *p_map, double *x_player, double *y_player)
{
	double	movestep;

	movestep = p_map->player.walk_dir * p_map->player.walk_speed;
	if (p_map->player.walk_side != 0)
	{
		if (p_map->player.walk_side == 1)
		{
			*y_player += cos(p_map->player.rot_angle)
				* p_map->player.walk_speed;
			*x_player -= sin(p_map->player.rot_angle)
				* p_map->player.walk_speed;
		}
		else
		{
			*y_player -= cos(p_map->player.rot_angle)
				* p_map->player.walk_speed;
			*x_player += sin(p_map->player.rot_angle)
				* p_map->player.walk_speed;
		}
	}
	else
	{
		*y_player += movestep * sin(p_map->player.rot_angle);
		*x_player += movestep * cos(p_map->player.rot_angle);
	}
}

void	animation(t_map *map)
{
	int	current_frame;
	int	previous_frame;

	current_frame = map->i % 30;
	previous_frame = (current_frame - 1 + 30) % 30;
	map->player_img[current_frame]->enabled = true;
	map->player_img[previous_frame]->enabled = false;
	map->i = (map->i + 1) % 30;
}

void exec (void *param)
{
	t_map	*p_map;

	p_map = (t_map *)param;
	animation(p_map);
}

void	keyfunc(mlx_key_data_t keydata, void *param)
{
	t_map	*p_map;
	double	x_player;
	double	y_player;
	int		key_use;

	p_map = (t_map *)param;
	x_player = p_map->player.x_double;
	y_player = p_map->player.y_double;
	key_use = check_key(keydata, p_map);
	if (!key_use)
		return ;
	p_map->player.rot_angle += p_map->player.turn_dir
		* p_map->player.turn_speed;
	update_player_position(p_map, &x_player, &y_player);
	if (!hit_wall(p_map, x_player, y_player, key_use))
	{
		p_map->player.y_double = y_player;
		p_map->player.x_double = x_player;
	}
	raycasting(p_map);
	key_release(p_map);
}

void cursorfunc(double xpos, double ypos, void* param)
{
	t_map			*p_map;
	double			delta_x;
	double			rotation_scale;
	static double	prev_xpos;
	static double	avg_delta_x;

	rotation_scale = 0.003;
	p_map = (t_map *)param;
	if (xpos < 0 || ypos < 0)
		xpos = 0;
	if (xpos > WIDTH || ypos > HEIGHT)
		xpos = WIDTH;
	delta_x = xpos - prev_xpos;
	prev_xpos = xpos;
	avg_delta_x = 0.9 * avg_delta_x + 0.2 * delta_x;
	p_map->player.rot_angle += avg_delta_x * rotation_scale;
	if (p_map->player.rot_angle >= 2 * M_PI)
		p_map->player.rot_angle -= 2 * M_PI;
	if (p_map->player.rot_angle < 0)
		p_map->player.rot_angle += 2 * M_PI;
	if (fabs(delta_x) > 1)
		raycasting(p_map);
}

void	move_player(t_map *p_map)
{
	mlx_cursor_hook(p_map->mlx, cursorfunc, p_map);
	mlx_key_hook(p_map->mlx, keyfunc, p_map);
	mlx_close_hook(p_map->mlx, close_win, p_map);
	mlx_loop_hook(p_map->mlx, exec, p_map);
}
