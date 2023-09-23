/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/23 15:42:00 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	map_element_color(t_map_element element)
{
	if (element == WALL)
		return (0x121212FF);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0xFFFFFF40);
	else if (element == SURFACE_PLAYABLE)
		return (0x918567FF);
	else if (element >= NORTH && element <= SOUTH)
		return (0x75003bFF);
	else
		return (0x0FFFFFFFF);
}

void	player_icon(t_global *data, int xm, int ym, int r, uint32_t color)
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
			mlx_put_pixel(data->hud_img, i, (ym + y), color);
			mlx_put_pixel(data->hud_img, i, (ym - y), color);
		}

		r = err;
		if (r <= y) err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	}
}

void	square(t_global *data, int x, int y, uint32_t color, int edge_size)
{
	int	left;
	int	top;
	int	right;
	int	bottom;

	left = x - edge_size / 2;
	top = y - edge_size / 2;
	right = x + edge_size / 2;
	bottom = y + edge_size / 2;
	for (int i = top; i <= bottom; i++)
	{
		for (int j = left; j <= right; j++)
		{
			if (i < MINIMAP_SIZE && j < MINIMAP_SIZE)
				mlx_put_pixel(data->hud_img, abs(j), abs(i), color);
		}
	}
}

void	draw_minimap_background(t_global *data)
{
	int x, y;
	int left = data->player.x * UNIT_SIZE - MINIMAP_SIZE / 2;
	int top = data->player.y * UNIT_SIZE - MINIMAP_SIZE / 2;
	int right = data->player.x * UNIT_SIZE + MINIMAP_SIZE / 2;
	int bottom = data->player.y * UNIT_SIZE + MINIMAP_SIZE / 2;

	y = (top - UNIT_SIZE) / UNIT_SIZE;
	while (y <= (bottom + UNIT_SIZE) / UNIT_SIZE)
	{
		x = (left - UNIT_SIZE) / UNIT_SIZE;
		while (x <= (right + UNIT_SIZE) / UNIT_SIZE)
		{
			if (x >= 0 && x <= (int)data->map->width && y >= 0 && y < (int)data->map->height)
			{
				int mapX = x * UNIT_SIZE;
				int mapY = y * UNIT_SIZE;
				if (data->map->map_array[y][x] >= NORTH && data->map->map_array[y][x] <= SOUTH)
					square(data, mapX - left, mapY - top, map_element_color(SURFACE_PLAYABLE), UNIT_SIZE);
				else
					square(data, mapX - left, mapY - top, map_element_color(data->map->map_array[y][x]), UNIT_SIZE);
			}
			x++;
		}
		y++;
	}
}

void minimap(t_global *data)
{
	square(data, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, 0xFFFFFF40, MINIMAP_SIZE);
	draw_minimap_background(data);
	player_icon(data, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, PLAYER_CIRCLE, map_element_color(NORTH));
}
