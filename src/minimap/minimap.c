/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:32:11 by me3za             #+#    #+#             */
/*   Updated: 2023/09/14 18:59:08 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_SQUARE 8
#define MINIMAP_CIRCLE 10

uint32_t	element_color(t_map_element element)
{
	if (element == WALL)
		return (0x0000FFFF);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0x00000000);
	else if (element == SURFACE_PLAYABLE)
		return (0x00FFFFFF);
	else if (element >= NORTH && element <= SOUTH)
		return (0xFF0000FF);
	else
		return (0x0FFFFFFFF);
}

// void	circle(t_global *data, int x, int y)
// {
// 	/* Look up circle formula */	
// }



void	square(t_global *data, int x, int y, uint32_t color)
{
	int j;
	int i;
	
	j = 0;
	while (j <= MINIMAP_SQUARE)
	{
		i = 0;
		while (i <= MINIMAP_SQUARE)
		{
			mlx_put_pixel(data->minimap_img, (x * MINIMAP_SQUARE + i) % WIN_WIDTH, (y * MINIMAP_SQUARE + j) % WIN_HEIGHT, color);
			i++;
		}
		j++;
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
			square(data, x, y, element_color(data->map->map_array[y][x]));
			x++;
		}
		y++;
	}
}

void	move_player(void *param)
{
	t_global *data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		square(data, data->player.x, data->player.y, element_color(SURFACE_PLAYABLE));
		if (data->map->map_array[(int)data->player.y - 1][(int)data->player.x] != WALL)
			data->player.y -= 0.5;
		square(data, data->player.x, data->player.y, element_color(NORTH));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		square(data, data->player.x, data->player.y, element_color(SURFACE_PLAYABLE));
		if (data->map->map_array[(int)data->player.y + 1][(int)data->player.x] != WALL)
			data->player.y += 0.5;
		square(data, data->player.x, data->player.y, element_color(NORTH));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		square(data, data->player.x, data->player.y, element_color(SURFACE_PLAYABLE));
		if (data->map->map_array[(int)data->player.y][(int)data->player.x + 1] != WALL)
			data->player.x += 0.5;
		square(data, data->player.x, data->player.y, element_color(NORTH));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		square(data, data->player.x, data->player.y, element_color(SURFACE_PLAYABLE));
		if (data->map->map_array[(int)data->player.y][(int)data->player.x - 1] != WALL)
			data->player.x -= 0.5;
		square(data, data->player.x, data->player.y, element_color(NORTH));
	}
}

void	minimap(t_global *data)
{
	draw_minimap(data);
	mlx_loop_hook(data->mlx, move_player, data);
}