/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:55:56 by relamine          #+#    #+#             */
/*   Updated: 2024/12/26 05:14:50 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_key(mlx_key_data_t keydata, t_map *p_map)
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
	{
		free_map(p_map);
		mlx_terminate(p_map->mlx);
		exit(0);
	}
	else 
		return (0);
	return (1);
}
void key_release(t_map *p_map)
{
	p_map->player.walk_dir = 0;
	p_map->player.turn_dir = 0;
	p_map->player.walk_side = 0;

}
void keyfunc(mlx_key_data_t keydata, void* param)
{
	t_map	*p_map;

	p_map = (t_map*)param;

	double x_player;
	double y_player;
	double movestep;

	x_player = p_map->player.x_double;
	y_player = p_map->player.y_double;

	if (check_key(keydata, p_map))
		ft_memset(p_map->map_img->pixels, 0, p_map->map_img->width * p_map->map_img->height * sizeof(int32_t));
	else
		return ;
	
	p_map->player.rot_angle += p_map->player.turn_dir * p_map->player.turn_speed;
	printf("rot_angle = %f\n", p_map->player.rot_angle);

	movestep = p_map->player.walk_dir * p_map->player.walk_speed;
	if (p_map->player.walk_side != 0)
	{
		if (p_map->player.walk_side == 1)
		{
			p_map->player.y_double += cos(p_map->player.rot_angle) * p_map->player.walk_speed;
			p_map->player.x_double -= sin(p_map->player.rot_angle) * p_map->player.walk_speed;	
		}
		else
		{
			p_map->player.y_double -= cos(p_map->player.rot_angle) * p_map->player.walk_speed;
			p_map->player.x_double += sin(p_map->player.rot_angle) * p_map->player.walk_speed;	
		}
	}
	else
	{
		p_map->player.y_double += movestep * sin(p_map->player.rot_angle);
		p_map->player.x_double += movestep * cos(p_map->player.rot_angle);	
	}
	printf("x = %f, y = %f\n", p_map->player.x_double, p_map->player.y_double);
	raycasting(p_map, p_map->mlx, p_map->map_img);
	printf("---------\n");
	key_release(p_map);
}

void move_player(t_map *p_map, mlx_t* mlx)
{
	mlx_key_hook(mlx, keyfunc, p_map);
}
