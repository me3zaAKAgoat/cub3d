/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/22 23:00:48 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x > map->width || y > map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL || map->map_array[(int)floor(y)][(int)floor(x)] == SURFACE_NOT_PLAYABLE)
		return (1);
	return (0);
}


bool	collides(t_global *data, t_move_direction move)
{
	if (move == forward)
		return (is_wall(data->map
		, data->player.x + MOVE_SPEED * cos(data->player.viewing_angle)
		, data->player.y + MOVE_SPEED * sin(data->player.viewing_angle)));
	else if (move == backward)
		return (is_wall(data->map
		, data->player.x - MOVE_SPEED * cos(data->player.viewing_angle )
		, data->player.y - MOVE_SPEED * sin(data->player.viewing_angle )));
	else if (move == right)
		return (is_wall(data->map
		, data->player.x + MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2)
		, data->player.y + MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2)));
	else
		return (is_wall(data->map
		, data->player.x + MOVE_SPEED * cos(data->player.viewing_angle - M_PI_2)
		, data->player.y + MOVE_SPEED * sin(data->player.viewing_angle - M_PI_2)));
}

bool	is_movement_key_down(t_global *data)
{
	return (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D) || mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT));
}

void	move_player(void *param)
{
	t_global	*data;

	data = param;
	if (is_movement_key_down(data))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->player.viewing_angle -= ROTATION_SPEED;
		if (mlx_is_key_down (data->mlx, MLX_KEY_RIGHT))
			data->player.viewing_angle += ROTATION_SPEED;
		if (mlx_is_key_down (data->mlx, MLX_KEY_W) && !collides(data, forward))
		{
			data->player.x += MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y += MOVE_SPEED * sin(data->player.viewing_angle);
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_S) && !collides(data, backward))
		{
			data->player.x -= MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y -= MOVE_SPEED * sin(data->player.viewing_angle);
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_D) && !collides(data, right))
		{
			data->player.x += MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2);
			data->player.y += MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2);
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_A) && !collides(data, left))
		{
			data->player.x += MOVE_SPEED * cos(data->player.viewing_angle - M_PI_2);
			data->player.y += MOVE_SPEED * sin(data->player.viewing_angle - M_PI_2);
		}
		draw_minimap_background(data);
		cast_all_rays(data);
		player_icon(data, data->player.x * UNIT_SIZE, data->player.y * UNIT_SIZE, PLAYER_CIRCLE, map_element_color(NORTH));
	}
}