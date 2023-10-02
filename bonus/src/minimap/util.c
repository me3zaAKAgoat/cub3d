/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:14:50 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/02 15:33:41 by echoukri         ###   ########.fr       */
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
		return (0xFFFFFF40);
}

void	minimap_bg_init(t_global *data, t_sides *sides, t_point *iterators)
{
	sides->left = data->player.x * UNIT_SIZE - MINIMAP_SIZE / 2;
	sides->top = data->player.y * UNIT_SIZE - MINIMAP_SIZE / 2;
	sides->right = data->player.x * UNIT_SIZE + MINIMAP_SIZE / 2;
	sides->bottom = data->player.y * UNIT_SIZE + MINIMAP_SIZE / 2;
	iterators->y = (sides->top - UNIT_SIZE) / UNIT_SIZE;
}

bool	player_sp(t_map_element **map_array, int x, int y)
{
	return (map_array[y][x] >= NORTH && map_array[y][x] <= SOUTH);
}

void	draw_minimap_unit(t_global *data, t_point *iterators, t_sides *sides)
{
	if (player_sp(data->map->map_array, iterators->x, iterators-> y))
		square(data, (t_double_couple){.x = \
		iterators->x * UNIT_SIZE - sides->left, .y = \
		iterators->y * UNIT_SIZE - sides->top}, \
		map_element_color(SURFACE_PLAYABLE), UNIT_SIZE);
	else
		square(data, (t_double_couple){.x = \
		iterators->x * UNIT_SIZE - sides->left, \
		.y = iterators->y * UNIT_SIZE - sides->top}, \
		map_element_color(data->map->map_array[iterators->y] \
		[iterators->x]), UNIT_SIZE);
}
