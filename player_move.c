/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:55:56 by relamine          #+#    #+#             */
/*   Updated: 2025/01/18 09:29:03 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_key(mlx_key_data_t keydata, t_map *p_map)
{
	if (keydata.action != MLX_REPEAT && keydata.action != MLX_PRESS)
		return (0);
	if (keydata.key == MLX_KEY_W)
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

void	keyfunc(mlx_key_data_t keydata, void *param)
{
	t_map	*p_map;
	double	x_player;
	double	y_player;

	p_map = (t_map *)param;
	x_player = p_map->player.x_double;
	y_player = p_map->player.y_double;
	if (!check_key(keydata, p_map))
		return ;
	p_map->player.rot_angle += p_map->player.turn_dir
		* p_map->player.turn_speed;
	update_player_position(p_map, &x_player, &y_player);
	if (!hit_wall(p_map, x_player, y_player))
	{
		p_map->player.y_double = y_player;
		p_map->player.x_double = x_player;
	}
	raycasting(p_map);
	key_release(p_map);
}

void	move_player(t_map *p_map)
{
	mlx_key_hook(p_map->mlx, keyfunc, p_map);
	mlx_close_hook(p_map->mlx, close_win, p_map);
}
