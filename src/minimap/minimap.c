/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/22 21:58:26 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	map_element_color(t_map_element element)
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
			mlx_put_pixel(data->hud_img, OFFSET_X + i, OFFSET_Y + (ym + y), color);
			mlx_put_pixel(data->hud_img, OFFSET_X + i, OFFSET_Y + (ym - y), color);
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
			mlx_put_pixel(data->hud_img, OFFSET_X + j, OFFSET_Y + i, color);
	}
}

void	draw_minimap_background(t_global *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map_list[y])
	{
		x = 0;
		while (data->map->map_list[y][x] != HORIZONTAL_TERM)
		{
			if (data->map->map_list[y][x] >= NORTH && data->map->map_list[y][x] <= SOUTH)
				square(data, x * UNIT_SIZE, y * UNIT_SIZE, map_element_color(SURFACE_PLAYABLE), UNIT_SIZE);
			else
				square(data, x * UNIT_SIZE, y * UNIT_SIZE, map_element_color(data->map->map_list[y][x]), UNIT_SIZE);
			x++;
		}
		y++;
	}
}

void	minimap(t_global *data)
{
	draw_minimap_background(data);
	cast_all_rays(data);
	player_icon(data, data->player.x * UNIT_SIZE, data->player.y * UNIT_SIZE, PLAYER_CIRCLE, map_element_color(NORTH));
}