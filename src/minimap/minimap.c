/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/19 04:32:00 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	element_color(t_map_element element)
{
	if (element == WALL)
		return (0x121212FF);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0x00000000);
	else if (element == SURFACE_PLAYABLE)
		return (0x918567FF);
	else if (element >= NORTH && element <= SOUTH)
		return (0x75003bFF);
	else
		return (0x0FFFFFFFF);
}

void	filled_circle(t_global *data, int xm, int ym, int r, uint32_t color)
{
	xm -= r;
	ym -= r;
	int	x;
	int	y;
	int	err;

	x = -r;
	y = 0;
	err = 2 - 2 * r;
	while (x < 0)
	{
		for (int i = xm + x; i <= xm - x; i++) {
			mlx_put_pixel(data->minimap_img, abs(OFFSET_X + i) % WIN_WIDTH, abs(OFFSET_Y + (ym + y)) % WIN_HEIGHT, color);
			mlx_put_pixel(data->minimap_img, abs(OFFSET_X + i) % WIN_WIDTH, abs(OFFSET_Y + (ym - y)) % WIN_HEIGHT, color);
		}

		r = err;
		if (r <= y) err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	}
}

void	square(t_global *data, int x, int y, uint32_t color, int rad)
{
	int	left;
	int	top;
	int	right;
	int	bottom;

	left = x - rad / 2;
	top = y - rad / 2;
	right = x + rad / 2;
	bottom = y + rad / 2;
	for (int i = top; i <= bottom; i++)
	{
		for (int j = left; j <= right; j++)
			mlx_put_pixel(data->minimap_img, (abs(OFFSET_X + j) + WIN_WIDTH) % WIN_WIDTH, (abs(OFFSET_Y + i) + WIN_HEIGHT) % WIN_HEIGHT, color);
	}
}

void	draw_minimap(t_global *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map_array[y])
	{
		x = 0;
		while (data->map->map_array[y][x] != HORIZONTAL_TERM)
		{
			if (data->map->map_array[y][x] >= NORTH && data->map->map_array[y][x] <= SOUTH)
				square(data, x * MINIMAP_UNIT, y * MINIMAP_UNIT, element_color(SURFACE_PLAYABLE), MINIMAP_UNIT);
			else
				square(data, x * MINIMAP_UNIT, y * MINIMAP_UNIT, element_color(data->map->map_array[y][x]), MINIMAP_UNIT);
			x++;
		}
		y++;
	}
}

bool	is_wall(int **map, double x, double y)
{
	if (map[(int)floor(y)][(int)floor(x)] == WALL)
		return (1);
	return (0);
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_global	*data;

	(void)keydata;
	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_Q) || mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		draw_minimap(data);
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			data->player.viewing_angle += ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->player.viewing_angle -= ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_UP)
			&& !is_wall(data->map->map_array 
			, data->player.x + MINIMAP_MOVE_SPEED * cos(data->player.viewing_angle)
			, data->player.y + MINIMAP_MOVE_SPEED * sin(data->player.viewing_angle)))
		{
			data->player.x += MINIMAP_MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y += MINIMAP_MOVE_SPEED * sin(data->player.viewing_angle);
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN)
			&& !is_wall(data->map->map_array
			, data->player.x - MINIMAP_MOVE_SPEED * cos(data->player.viewing_angle)
			, data->player.y - MINIMAP_MOVE_SPEED * sin(data->player.viewing_angle)))
		{
			data->player.x -= MINIMAP_MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y -= MINIMAP_MOVE_SPEED * sin(data->player.viewing_angle);
		}
		cast_all_rays(data);
		filled_circle(data, data->player.x * MINIMAP_UNIT, data->player.y * MINIMAP_UNIT, PLAYER_CIRCLE, element_color(NORTH));
	}
}

void	minimap(t_global *data)
{
	draw_minimap(data);
	cast_all_rays(data);
	filled_circle(data, data->player.x * MINIMAP_UNIT, data->player.y * MINIMAP_UNIT, PLAYER_CIRCLE, element_color(NORTH));
	mlx_key_hook(data->mlx, move_player, data);
}