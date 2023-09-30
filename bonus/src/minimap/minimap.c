/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/30 12:03:10 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		i = xm + x -1;
		while (++i <= xm - x)
			player_pixel(data->hud_img, i, y, ym);
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	}
}

void	square(t_global *data, t_double_couple xy, \
		uint32_t color, int edge_size)
{
	t_point	iterators;

	data->square.left = xy.x - edge_size / 2;
	data->square.top = xy.y - edge_size / 2;
	data->square.right = xy.x + edge_size / 2;
	data->square.bottom = xy.y + edge_size / 2;
	iterators.y = data->square.top;
	while (iterators.y <= data->square.bottom)
	{
		iterators.x = data->square.left;
		while (iterators.x <= data->square.right)
		{
			if (iterators.x < MINIMAP_SIZE && iterators.y < MINIMAP_SIZE)
				mlx_put_pixel(data->hud_img, abs(iterators.x), \
				abs(iterators.y), color);
			iterators.x++;
		}
		iterators.y++;
	}
}

void	draw_minimap(t_global *data)
{
	data->draw.left = data->player.x * UNIT_SIZE - MINIMAP_SIZE / 2;
	data->draw.top = data->player.y * UNIT_SIZE - MINIMAP_SIZE / 2;
	data->draw.right = data->player.x * UNIT_SIZE + MINIMAP_SIZE / 2;
	data->draw.bottom = data->player.y * UNIT_SIZE + MINIMAP_SIZE / 2;
}

void	draw_minimap_background(t_global *data, t_point iterators)
{
	draw_minimap(data);
	iterators.y = ((data->draw.top - UNIT_SIZE) / UNIT_SIZE) - 1;
	while (iterators.y++ <= (data->draw.bottom + UNIT_SIZE) / UNIT_SIZE)
	{
		iterators.x = (data->draw.left - UNIT_SIZE) / UNIT_SIZE;
		while (iterators.x <= (data->draw.right + UNIT_SIZE) / UNIT_SIZE)
		{
			if (iterators.x >= 0 && iterators.x <= (int)data->map->width && \
				iterators.y >= 0 && iterators.y < (int)data->map->height)
			{
				if (data->map->map_array[iterators.y][iterators.x] >= NORTH \
					&& data->map->map_array[iterators.y][iterators.x] <= SOUTH)
					square(data, (t_double_couple){.x = iterators.x * UNIT_SIZE \
					- data->draw.left, .y = iterators.y * UNIT_SIZE - \
					data->draw.top}, map_element_color(SURFACE_PLAYABLE), \
					UNIT_SIZE);
				else
					square(data, (t_double_couple){.x = iterators.x * UNIT_SIZE \
					- data->draw.left, .y = iterators.y * UNIT_SIZE - \
					data->draw.top}, map_element_color(data->map->map_array \
					[iterators.y][iterators.x]), UNIT_SIZE);
			}
			iterators.x++;
		}
	}
}

void	minimap(t_global *data)
{
	t_point	iterators;

	square(data, (t_double_couple){.x = MINIMAP_SIZE / 2, \
		.y = MINIMAP_SIZE / 2}, 0xFFFFFF40, MINIMAP_SIZE);
	draw_minimap_background(data, iterators);
	player_icon(data, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, UNIT_SIZE / 2);
}
