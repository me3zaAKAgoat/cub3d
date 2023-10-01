/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 14:22:23 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_wall(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL
		|| map->map_array[(int)floor(y)][(int)floor(x)] == SURFACE_NOT_PLAYABLE
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_CLOSED)
		return (1);
	return (0);
}

void	cursor_handler(double x, double y, void *param)
{
	t_global	*data;

	(void)y;
	data = param;
	if (!data->cursor_enabled)
	{
		if (x > WIN_WIDTH / 2)
			data->player.viewing_angle += (x - WIN_WIDTH / 2) * .001;
		else if (x < WIN_WIDTH / 2)
			data->player.viewing_angle += (x - WIN_WIDTH / 2) * .001;
		mlx_set_mouse_pos(data->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
}

bool	hitbox_compromised(t_global *data, double viewing_angle)
{
	t_ray	ray;

	ray.angle = sanitize_angle(viewing_angle);
	ray.is_facing_right = is_facing_right(ray.angle);
	ray.is_facing_up = is_facing_up(ray.angle);
	ray.distance = intersection_distance(data->map,
			data->player.x, data->player.y, &ray);
	if (ray.distance < HITBOX_SIZE)
		return (true);
	return (false);
}

bool	is_movement_key_down(t_global *data)
{
	return (mlx_is_key_down(data->mlx, MLX_KEY_W)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D)
		|| mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_Q));
}

void	move_player(void *param)
{
	t_global	*data;

	data = param;
	data->steps.fs_xstep = MOVE_SPEED * cos(data->player.viewing_angle);
	data->steps.fs_ystep = MOVE_SPEED * sin(data->player.viewing_angle);
	data->steps.lr_xstep = MOVE_SPEED * \
	cos(data->player.viewing_angle + M_PI_2);
	data->steps.lr_ystep = MOVE_SPEED * \
	sin(data->player.viewing_angle + M_PI_2);
	move_player_ut(data);
	render_game(data);
}
