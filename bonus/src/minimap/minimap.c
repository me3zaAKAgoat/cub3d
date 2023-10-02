/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/02 17:00:00 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_cirlce_portion(t_global *data, t_point p, t_point pm)
{
	int	i;
	int	xm;
	int	ym;
	int	x;
	int	y;

	xm = pm.x;
	ym = pm.y;
	x = p.x;
	y = p.y;
	i = xm + x;
	while (i <= xm - x)
	{
		mlx_put_pixel(data->hud_img, i, (ym + y), PLAYER_COLOR);
		mlx_put_pixel(data->hud_img, i, (ym - y), PLAYER_COLOR);
		i++;
	}
}

void	player_icon(t_global *data, int xm, int ym, int r)
{
	int	x;
	int	y;
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
		draw_cirlce_portion(data, (t_point){.x = x, .y = y}, \
		(t_point){.x = xm, .y = ym});
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	}
}

void	square(t_global *data, t_double_couple xy,
		uint32_t color, int edge_size)
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
				mlx_put_pixel(data->hud_img, \
				abs(iterators.x), abs(iterators.y), color);
			iterators.x++;
		}
		iterators.y++;
	}
}

void	draw_minimap_background(t_global *data)
{
	t_point	iterators;
	t_sides	sides;

	minimap_bg_init(data, &sides, &iterators);
	while (iterators.y <= (sides.bottom + UNIT_SIZE) / UNIT_SIZE)
	{
		iterators.x = (sides.left - UNIT_SIZE) / UNIT_SIZE;
		while (iterators.x <= (sides.right + UNIT_SIZE) / UNIT_SIZE)
		{
			if (iterators.x >= 0 && iterators.x <= (int)data->map->width
				&& iterators.y >= 0 && iterators.y < (int)data->map->height)
			{
				draw_minimap_unit(data, &iterators, &sides);
			}
			iterators.x++;
		}
		iterators.y++;
	}
}

void	minimap(t_global *data)
{
	square(data, (t_double_couple){.x = MINIMAP_SIZE / 2, \
	.y = MINIMAP_SIZE / 2}, 0xFFFFFF20, MINIMAP_SIZE);
	draw_minimap_background(data);
	player_icon(data, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, UNIT_SIZE / 2);
}
