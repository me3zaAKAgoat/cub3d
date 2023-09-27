/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/27 21:49:04 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL || map->map_array[(int)floor(y)][(int)floor(x)] == SURFACE_NOT_PLAYABLE
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_CLOSED)
		return (1);
	return (0);
}

void	cursor_handler(double x, double y, void *param)
{
	t_global	*data;
	
	(void)y;
	data = param;
	if (data->cursor_enabled)
		return ;
	if (x > WIN_WIDTH / 2)
		data->player.viewing_angle += (x - WIN_WIDTH / 2) * .001;
	else if (x < WIN_WIDTH / 2)
		data->player.viewing_angle += (x - WIN_WIDTH / 2) * .001;
	mlx_set_mouse_pos(data->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return ;
}
void	interact_with_door(t_global *data)
{
	t_ray			ray;
	t_map_element	*door;

	ray.angle = sanitize_angle(data->player.viewing_angle);
	ray.is_facing_right = is_facing_right(ray.angle);
	ray.is_facing_up = is_facing_up(ray.angle);
	ray.distance = intersection_distance_kms(data->map, data->player.x, data->player.y, &ray);
	if (ray.hit_vertical)
		door = data->map->map_array[(int)ray.wall_hit_vertical.y] + (int)ray.wall_hit_vertical.x + iternary(!ray.is_facing_right, -1, 0);
	if (!ray.hit_vertical)
		door = data->map->map_array[(int)ray.wall_hit_horizontal.y + iternary(ray.is_facing_up, -1, 0)] + (int)ray.wall_hit_horizontal.x;
	if (ray.distance < 2)
	{
		if (*door == DOOR_CLOSED)
			*door = DOOR_OPEN;
		else if (*door == DOOR_OPEN)
			*door = DOOR_CLOSED;
	}
}

bool	hitbox_compromised(t_global *data, double viewing_angle)
{
	t_ray	ray;

	ray.angle = sanitize_angle(viewing_angle);
	ray.is_facing_right = is_facing_right(ray.angle);
	ray.is_facing_up = is_facing_up(ray.angle);
	ray.distance = intersection_distance(data->map, data->player.x, data->player.y, &ray);
	if (ray.distance < HITBOX_SIZE)
		return (true);
	return (false);
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
	double		fs_xstep;
	double		fs_ystep;
	double		lr_xstep;
	double		lr_ystep;
	
	data = param;
	fs_xstep = MOVE_SPEED * cos(data->player.viewing_angle);
	fs_ystep = MOVE_SPEED * sin(data->player.viewing_angle);
	lr_xstep = MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2);
	lr_ystep = MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2);
	if (is_movement_key_down(data))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->player.viewing_angle -= ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			data->player.viewing_angle += ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_W) && !hitbox_compromised(data, data->player.viewing_angle))
		{
			data->player.x += fs_xstep;
			data->player.y += fs_ystep;
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_S) && !hitbox_compromised(data, data->player.viewing_angle + M_PI))
		{
			data->player.x -= fs_xstep;
			data->player.y -= fs_ystep;
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_D) && !hitbox_compromised(data, data->player.viewing_angle + M_PI_2))
		{
			data->player.x += lr_xstep;
			data->player.y += lr_ystep;
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_A) && !hitbox_compromised(data, data->player.viewing_angle - M_PI_2))
		{
			data->player.x -= lr_xstep;
			data->player.y -= lr_ystep;
		}
	}
	render_game(data);
}