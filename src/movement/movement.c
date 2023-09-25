/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:44:29 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/25 21:59:34 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL || map->map_array[(int)floor(y)][(int)floor(x)] == DOOR)
		return (1);
	return (0);
}
bool	check_collision(double x, double y, t_global *data)
{
	double old_x;
	double old_y;
	old_x = data->player.x;
	old_y = data->player.y;
	if ((data->map->map_array[(int)floor(y)][(int)floor(old_x)] == WALL && (data->map->map_array[(int)floor(old_y)][(int)floor(x)] \
		== WALL) || data->map->map_array[(int)floor(y)][(int)floor(x)] == DOOR ))
		return (1);
	if (data->map->map_array[(int)(y)][(int)(x)] == WALL)
		return (1);
	return (0);
}

bool	collides(t_global *data, t_move_direction move)
{
	if (move == forward)
		return (check_collision(data->player.x + (MOVE_SPEED + 0.2) * cos(data->player.viewing_angle)
		, data->player.y + (MOVE_SPEED + 0.2) * sin(data->player.viewing_angle), data));
	else if (move == backward)
		return (check_collision(data->player.x - (MOVE_SPEED + 0.2) * cos(data->player.viewing_angle )
		, data->player.y - (MOVE_SPEED + 0.2) * sin(data->player.viewing_angle ), data));
	else if (move == right)
		return (check_collision(data->player.x + (MOVE_SPEED + 0.2) * cos(data->player.viewing_angle + M_PI_2)
		, data->player.y + (MOVE_SPEED + 0.2) * sin(data->player.viewing_angle + M_PI_2), data));
	else
		return (check_collision(data->player.x + (MOVE_SPEED + 0.2) * cos(data->player.viewing_angle - M_PI_2)
		, data->player.y+ (MOVE_SPEED + 0.2) * sin(data->player.viewing_angle - M_PI_2), data));
}

bool	is_movement_key_down(t_global *data)
{
	return (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D) || mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_O) || mlx_is_key_down(data->mlx, MLX_KEY_C));
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
		if(mlx_is_key_down(data->mlx, MLX_KEY_C) && !data->is_door)
		{
			data->is_door = 1;
			ft_door(data, 1);
		}
		 if(mlx_is_key_down(data->mlx, MLX_KEY_O) && data->is_door)
		{
			data->is_door = 0;
			ft_door(data, 0);
		}
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
