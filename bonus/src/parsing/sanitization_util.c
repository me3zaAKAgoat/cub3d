/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitization_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:07:34 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/26 18:12:58 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	contacts_void_above(t_map *map, size_t x, size_t y)
{
	if (y == 0)
		return (true);
	if (map->map_array[y - 1][x] == SURFACE_NOT_PLAYABLE)
		return (true);
	return (false);
}

bool	contacts_void_down(t_map *map, size_t x, size_t y)
{
	if (y == map->height - 1)
		return (true);
	if (map->map_array[y + 1][x] == SURFACE_NOT_PLAYABLE)
		return (true);
	return (false);
}

bool	contacts_void_right(t_map *map, size_t x, size_t y)
{
	if (map->map_array[y][x + 1] == SURFACE_NOT_PLAYABLE
		|| map->map_array[y][x + 1] == HORIZONTAL_TERM)
		return (true);
	return (false);
}

bool	contacts_void_left(t_map *map, size_t x, size_t y)
{
	if (x == 0)
		return (true);
	if (map->map_array[y][x - 1] == SURFACE_NOT_PLAYABLE)
		return (true);
	return (false);
}

bool	contacts_void(t_map *map, size_t x, size_t y)
{
	return (contacts_void_above(map, x, y) || contacts_void_down(map, x, y)
		|| contacts_void_right(map, x, y) || contacts_void_left(map, x, y));
}
