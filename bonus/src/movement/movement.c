/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/26 21:04:06 by echoukri         ###   ########.fr       */
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

void	interact_with_door(t_global *data)
{
	t_map_element	*up;
	t_map_element	*down;
	t_map_element	*right;
	t_map_element	*left;

	up = data->map->map_array[(int)data->player.y + 1] + (int)data->player.x;
	down = data->map->map_array[(int)data->player.y - 1] + (int)data->player.x;
	right = data->map->map_array[(int)data->player.y] + (int)data->player.x + 1;
	left = data->map->map_array[(int)data->player.y] + (int)data->player.x - 1;
	if (*up == DOOR_CLOSED || *up == DOOR_OPEN)
		*up = iternary(*up == DOOR_CLOSED, DOOR_OPEN, DOOR_CLOSED);
	else if (*down == DOOR_CLOSED || *down == DOOR_OPEN)
		*down = iternary(*down == DOOR_CLOSED, DOOR_OPEN, DOOR_CLOSED);
	else if (*right == DOOR_CLOSED || *right == DOOR_OPEN)
		*right = iternary(*right == DOOR_CLOSED, DOOR_OPEN, DOOR_CLOSED);
	else if (*left == DOOR_CLOSED || *left == DOOR_OPEN)
		*left = iternary(*left == DOOR_CLOSED, DOOR_OPEN, DOOR_CLOSED);
}

bool	hitbox_compromised(t_map *map, double x, double y)
{
	t_ray	ray;

	ray.angle = 0;
	while (ray.angle <= PI * 2)
	{
		ray.is_facing_right = is_facing_right(ray.angle);
		ray.is_facing_up = is_facing_up(ray.angle);
		ray.distance = intersection_distance(map, x, y, &ray);
		if (ray.distance < HITBOX_SIZE)
			return (true);
		ray.angle += M_PI_4 / 10;
	}
	return (false);
}

bool	collides(t_global *data, t_move_direction move)
{
	if (move == forward)
		return (hitbox_compromised(data->map
		, data->player.x + MOVE_SPEED * cos(data->player.viewing_angle)
		, data->player.y + MOVE_SPEED * sin(data->player.viewing_angle)));
	else if (move == backward)
		return (hitbox_compromised(data->map
		, data->player.x - MOVE_SPEED * cos(data->player.viewing_angle )
		, data->player.y - MOVE_SPEED * sin(data->player.viewing_angle )));
	else if (move == right)
		return (hitbox_compromised(data->map
		, data->player.x + MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2)
		, data->player.y + MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2)));
	else
		return (hitbox_compromised(data->map
		, data->player.x + MOVE_SPEED * cos(data->player.viewing_angle - M_PI_2)
		, data->player.y + MOVE_SPEED * sin(data->player.viewing_angle - M_PI_2)));
}

bool	is_movement_key_down(t_global *data)
{
	return (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D) || mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT));
}
#include <time.h>
void	move_player(void *param)
{
	t_global	*data;
	double		fs_xstep;
	double		fs_ystep;
	double		lr_xstep;
	double		lr_ystep;
	
	/* fps logic */
	clock_t start_time, end_time;
	static mlx_image_t *x;
	start_time = clock();
	/* fps logic */
	
	data = param;
	fs_xstep = MOVE_SPEED * cos(data->player.viewing_angle);
	fs_ystep = MOVE_SPEED * sin(data->player.viewing_angle);
	lr_xstep = MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2);
	lr_ystep = MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2);
	if (is_movement_key_down(data))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->player.viewing_angle -= ROTATION_SPEED;
		if (mlx_is_key_down (data->mlx, MLX_KEY_RIGHT))
			data->player.viewing_angle += ROTATION_SPEED;
		if (mlx_is_key_down (data->mlx, MLX_KEY_W) && !collides(data, forward))
		{
			data->player.x += fs_xstep;
			data->player.y += fs_ystep;
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_S) && !collides(data, backward))
		{
			data->player.x -= fs_xstep;
			data->player.y -= fs_ystep;
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_D) && !collides(data, right))
		{
			data->player.x += lr_xstep;
			data->player.y += lr_ystep;
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_A) && !collides(data, left))
		{
			data->player.x -= lr_xstep;
			data->player.y -= lr_ystep;
		}
		render_game(data);
	}
	
	/* fps logic */
	end_time = clock();
	mlx_delete_image(data->mlx, x);
	double dfps = 1 / ((double)(end_time - start_time) / CLOCKS_PER_SEC);
	char *fps = ft_itoa(dfps);
	x = mlx_put_string(data->mlx, dfps > 300 ? "300" : fps, WIN_WIDTH - 50, 10);
	free(fps);
	/* fps logic */
}