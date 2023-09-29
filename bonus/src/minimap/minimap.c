/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/29 15:54:49 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	map_element_color(t_map_element element)
{
	if (element == WALL)
		return (0x121212FF);
	else if (element == DOOR_CLOSED)
		return (0xf57542FF);
	else if (element == DOOR_OPEN)
		return (0x4bde53FF);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0xFFFFFF40);
	else if (element == SURFACE_PLAYABLE)
		return (0x7F7F7FFF);
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
		return (mlx_put_pixel(data->hud_img, xm, ym, PLAYER_COLOR));
	x = -r;
	y = 0;
	err = 2 - 2 * r;
	while (x < 0)
	{
		i = xm + x;
		while (i <= xm - x)
		{
			mlx_put_pixel(data->hud_img, i, (ym + y), PLAYER_COLOR);
			mlx_put_pixel(data->hud_img, i, (ym - y), PLAYER_COLOR);
			i++;
		}
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	}
}

void	square(t_global *data, t_double_couple xy, uint32_t color, int edge_size)
{
	int		left;
	int		top;
	int		right;
	int		bottom;
	t_point	iterators;

	left = xy.x - edge_size / 2;
	top = xy.y - edge_size / 2;
	right = xy.x + edge_size / 2;
	bottom = xy.y + edge_size / 2;
	iterators.y = top;
	while (iterators.y <= bottom)
	{
		iterators.x = left;
		while (iterators.x <= right)
		{
			if (iterators.x < MINIMAP_SIZE && iterators.y < MINIMAP_SIZE)
				mlx_put_pixel(data->hud_img, abs(iterators.x), abs(iterators.y), color);
			iterators.x++;
		}
		iterators.y++;
	}
}

void	draw_minimap_background(t_global *data)
{
	t_point iterators;
	int left = data->player.x * UNIT_SIZE - MINIMAP_SIZE / 2;
	int top = data->player.y * UNIT_SIZE - MINIMAP_SIZE / 2;
	int right = data->player.x * UNIT_SIZE + MINIMAP_SIZE / 2;
	int bottom = data->player.y * UNIT_SIZE + MINIMAP_SIZE / 2;

	iterators.y = (top - UNIT_SIZE) / UNIT_SIZE;
	while (iterators.y <= (bottom + UNIT_SIZE) / UNIT_SIZE)
	{
		iterators.x = (left - UNIT_SIZE) / UNIT_SIZE;
		while (iterators.x <= (right + UNIT_SIZE) / UNIT_SIZE)
		{
			if (iterators.x >= 0 && iterators.x <= (int)data->map->width && iterators.y >= 0 && iterators.y < (int)data->map->height)
			{
				if (data->map->map_array[iterators.y][iterators.x] >= NORTH && data->map->map_array[iterators.y][iterators.x] <= SOUTH)
					square(data, (t_double_couple){.x = iterators.x * UNIT_SIZE - left, .y = iterators.y * UNIT_SIZE - top}, map_element_color(SURFACE_PLAYABLE), UNIT_SIZE);
				else
					square(data, (t_double_couple){.x = iterators.x * UNIT_SIZE - left, .y = iterators.y * UNIT_SIZE - top}, map_element_color(data->map->map_array[iterators.y][iterators.x]), UNIT_SIZE);
			}
			iterators.x++;
		}
		iterators.y++;
	}
}

void minimap(t_global *data)
{
	square(data, (t_double_couple){.x = MINIMAP_SIZE / 2, .y = MINIMAP_SIZE / 2}, 0xFFFFFF40, MINIMAP_SIZE);
	draw_minimap_background(data);
	player_icon(data, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, UNIT_SIZE / 2);
}
