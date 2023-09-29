/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:53:14 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 18:15:07 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall_kms(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL || \
		map->map_array[(int)floor(y)][(int)floor(x)] == SURFACE_NOT_PLAYABLE \
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_CLOSED \
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_OPEN)
		return (1);
	return (0);
}

bool	is_wall(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL | \
		map->map_array[(int)floor(y)][(int)floor(x)] == SURFACE_NOT_PLAYABLE
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_CLOSED)
		return (1);
	return (0);
}

bool	is_movement_key_down(t_global *data)
{
	return (mlx_is_key_down(data->mlx, MLX_KEY_W)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D)
		|| mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT));
}

void	move_player_ut(t_global *data)
{
	if (is_movement_key_down(data))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->player.view_angle -= ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			data->player.view_angle += ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_W) && \
			!hitbox_compromised(data, data->player.view_angle))
			key_move_up_down(data, PLUS);
		if (mlx_is_key_down(data->mlx, MLX_KEY_S) && \
			!hitbox_compromised(data, data->player.view_angle + M_PI))
			key_move_up_down(data, MINUS);
		if (mlx_is_key_down(data->mlx, MLX_KEY_D) && \
			!hitbox_compromised(data, data->player.view_angle + M_PI_2))
			key_move_left_right(data, PLUS);
		if (mlx_is_key_down(data->mlx, MLX_KEY_A) && \
			!hitbox_compromised(data, data->player.view_angle - M_PI_2))
			key_move_left_right(data, MINUS);
	}
}
