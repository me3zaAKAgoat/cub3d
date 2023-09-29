/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:00:54 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 17:28:27 by selhilal         ###   ########.fr       */
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

void	player_pixel(mlx_image_t *img, int i, int y, int ym)
{
	mlx_put_pixel(img, i, ym + y, map_element_color(NORTH));
	mlx_put_pixel(img, i, ym - y, map_element_color(NORTH));
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
			player_pixel(data->hud_img, i, y, ym);
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	}
}
