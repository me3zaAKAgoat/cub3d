/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/28 01:50:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	map_element_color(t_map_element element)
{
	if (element == WALL)
		return (0x121212FF);
	else if (element == DOOR_CLOSED)
		return (0x0be3dfFF);
	else if (element == DOOR_OPEN)
		return (0x8e3fe8FF);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0xFFFFFF40);
	else if (element == SURFACE_PLAYABLE)
		return (0x918567FF);
	else if (element >= NORTH && element <= SOUTH)
		return (0x75003bFF);
	else
		return (0x0FFFFFFFF);
}

void	player_icon(t_global *data, int xm, int ym, int r)
{
	int	x;
	int	y;
	int	i;
	int	err;

	xm -= r;
	ym -= r;
	if (r < 2)
		return (mlx_put_pixel(data->hud_img, xm, ym, map_element_color(NORTH)));
	x = -r;
	y = 0;
	err = 2 - 2 * r;
	while (x < 0)
	{
		i = xm + x - 1;
		while (++i <= xm - x)
		{
			mlx_put_pixel(data->hud_img, i, (ym + y), map_element_color(NORTH));
			mlx_put_pixel(data->hud_img, i, (ym - y), map_element_color(NORTH));
		}
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
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
	int	i;
	int j;

	left = x - edge_size / 2;
	top = y - edge_size / 2;
	right = x + edge_size / 2;
	bottom = y + edge_size / 2;
	i = top;
	while (i <= bottom)
	{
		j = left;
		while (j <= right)
		{
			if (i < MINIMAP_SIZE && j < MINIMAP_SIZE)
				mlx_put_pixel(data->hud_img, abs(j), abs(i), color);
			j++;
		}
		i++;
	}
}

void	draw_square(int x, int y, t_global *data)
{
	int	mapx;
	int	mapy;

	mapx = x * UNIT_SIZE;
	mapy = y * UNIT_SIZE;
	if (data->map->map_array[y][x] >= NORTH && \
		data->map->map_array[y][x] <= SOUTH)
		square(data, mapx - data->left, mapy - data->top, \
			map_element_color(SURFACE_PLAYABLE), UNIT_SIZE);
	else
		square(data, mapx - data->left, mapy - data->top, \
			map_element_color(data->map->map_array[y][x]), UNIT_SIZE);
}

void	draw_minimap_background(t_global *data, int x, int y)
{
	data->left = data->player.x * UNIT_SIZE - MINIMAP_SIZE / 2;
	data->top = data->player.y * UNIT_SIZE - MINIMAP_SIZE / 2;
	data->right = data->player.x * UNIT_SIZE + MINIMAP_SIZE / 2;
	data->bottom = data->player.y * UNIT_SIZE + MINIMAP_SIZE / 2;
	y = (data->top - UNIT_SIZE) / UNIT_SIZE;
	while (y <= (data->bottom + UNIT_SIZE) / UNIT_SIZE)
	{
		x = (data->left - UNIT_SIZE) / UNIT_SIZE;
		while (x <= (data->right + UNIT_SIZE) / UNIT_SIZE)
		{
			if (x >= 0 && x <= (int)data->map->width && y >= 0 && y < \
				(int)data->map->height)
				draw_square(x, y, data);
			x++;
		}
		y++;
	}
}

void	minimap(t_global *data)
{
	square(data, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, 0xFFFFFF40, MINIMAP_SIZE);
	draw_minimap_background(data, 0, 0);
	player_icon(data, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, UNIT_SIZE / 2);
}
