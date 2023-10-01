/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:41:16 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 17:34:08 by echoukri         ###   ########.fr       */
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

void	move_fb(t_global *data, t_double_couple *fs_step, bool forward)
{
	if (forward)
	{
		data->player.x += fs_step->x;
		data->player.y += fs_step->y;
	}
	else
	{
		data->player.x -= fs_step->x;
		data->player.y -= fs_step->y;
	}
}

void	move_lr(t_global *data, t_double_couple *lr_step, bool right)
{
	if (right)
	{
		data->player.x += lr_step->x;
		data->player.y += lr_step->y;
	}
	else
	{
		data->player.x -= lr_step->x;
		data->player.y -= lr_step->y;
	}
}
