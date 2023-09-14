/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/14 05:01:38 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SQUARE 20

uint32_t	element_color(t_map_element element)
{
	if (element == WALL)
		return (0xFF00FF00);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0x0000FF00);
	else if (element == SURFACE_PLAYABLE)
		return (0x000000FF);
	else if (element >= NORTH && element <= SOUTH)
		return (0x00FF0000);
	else
		return (0x00FFFFFF);
}

void	square(t_global *data, int x, int y)
{
	int j;
	int i;

	printf("x : %d y : %d\n", x, y);
	j = 0;
	while (j <= SQUARE)
	{
		i = 0;
		while (i <= SQUARE)
		{
			mlx_put_pixel(data->minimap_img, x + i, y + j, element_color(data->map->map_array[y][x]));
			i++;
		}
		j++;
	}
}

void	minimap(t_global *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map_array[y])
	{
		x = 0;
		while (data->map->map_array[y][x] != HORIZONTAL_TERM)
		{
			square(data, x * SQUARE, y * SQUARE);
			x++;
		}
		y++;
	}
}