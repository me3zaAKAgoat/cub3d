/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/17 02:08:30 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_SQUARE 8
#define MINIMAP_CIRCLE 4
#define OFFSET_X 4
#define OFFSET_Y 4

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

void filled_circle(t_global *data, int xm, int ym, int r, uint32_t color, int unit)
{
	int x = -r, y = 0, err = 2 - 2 * r;
	do {
		for (int i = xm * unit + x; i <= xm * unit - x; i++) {
			mlx_put_pixel(data->minimap_img, abs(OFFSET_X + i) % WIN_WIDTH, abs(OFFSET_Y + (ym * unit + y)) % WIN_HEIGHT, color);
			mlx_put_pixel(data->minimap_img, abs(OFFSET_X + i) % WIN_WIDTH, abs(OFFSET_Y + (ym * unit - y)) % WIN_HEIGHT, color);
		}

		r = err;
		if (r <= y) err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	} while (x < 0);
}

void square(t_global *data, int x, int y, uint32_t color, int rad)
{
	int halfSize = rad / 2;
	int left = x - halfSize;
	int top = y - halfSize;
	int right = x + halfSize;
	int bottom = y + halfSize;

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
				square(data, x * MINIMAP_SQUARE, y * MINIMAP_SQUARE, element_color(SURFACE_PLAYABLE), MINIMAP_SQUARE);
			else
				square(data, x * MINIMAP_SQUARE, y * MINIMAP_SQUARE, element_color(data->map->map_array[y][x]), MINIMAP_SQUARE);
			x++;
		}
		y++;
	}
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_global *data;

	(void)keydata;
	data = param;
	draw_minimap(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_UP) && data->map->map_array[(int)data->player.y - 1][(int)data->player.x] != WALL)
				data->player.y -= 1;
		if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) && data->map->map_array[(int)data->player.y + 1][(int)data->player.x] != WALL)
				data->player.y += 1;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) && data->map->map_array[(int)data->player.y][(int)data->player.x + 1] != WALL)
				data->player.x += 1;
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) && data->map->map_array[(int)data->player.y][(int)data->player.x - 1] != WALL)
				data->player.x -= 1;
	}
	filled_circle(data, data->player.x, data->player.y, MINIMAP_CIRCLE, element_color(NORTH), MINIMAP_SQUARE);
}

void	put_player_on_map(t_global *data)
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
				filled_circle(data, x, y, MINIMAP_CIRCLE, element_color(NORTH), MINIMAP_SQUARE);
			x++;
		}
		y++;
	}	
}

void	minimap(t_global *data)
{
	draw_minimap(data);
	put_player_on_map(data);
	mlx_key_hook(data->mlx, move_player, data);
}