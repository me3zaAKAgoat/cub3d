/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:49:18 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/26 21:46:06 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	contacts_void_above(t_map *map, int x, int y)
{
	if (y == 0)
		return (true);
	if (map->map_array[y - 1][x] == SURFACE_NOT_PLAYABLE)
		return (true);
	return (false);
}

bool	contacts_void_down(t_map *map, int x, int y)
{
	if (y == map->height - 1)
		return (true);
	if (map->map_array[y + 1][x] == SURFACE_NOT_PLAYABLE)
		return (true);
	return (false);
}

bool	contacts_void_right(t_map *map, int x, int y)
{
	if (map->map_array[y][x + 1] == SURFACE_NOT_PLAYABLE || map->map_array[y][x + 1] == HORIZONTAL_TERM)
		return (true);
	return (false);
}

bool	contacts_void_left(t_map *map, int x, int y)
{
	if (x == 0)
		return (true);
	if (map->map_array[y][x - 1] == SURFACE_NOT_PLAYABLE)
		return (true);
	return (false);
}

bool	contacts_void(t_map *map, int x, int y)
{
	return (contacts_void_above(map, x, y) || contacts_void_down(map, x, y)
		|| contacts_void_right(map, x, y) || contacts_void_left(map, x, y));
}

bool	is_player(t_map *map, int x, int y)
{
	return ((map->map_array[y][x] == NORTH || map->map_array[y][x] == WEST
		|| map->map_array[y][x] == SOUTH || map->map_array[y][x] == EAST));
}

void	sanitize_map(t_map *map)
{
	int x;
	int y;
	int player_count;

	y = 0;
	player_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x <= map->width)
		{
			if (is_player(map, x, y))
				player_count++;
			if ((map->map_array[y][x] == SURFACE_PLAYABLE || is_player(map, x, y)) && contacts_void(map, x, y))
				return (werror("Error\nMap not well enclosed."), exit(1));
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (werror("Error\nNumber of players is abnormal."), exit(1));
}
