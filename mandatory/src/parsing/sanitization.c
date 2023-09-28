/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:49:18 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/28 09:47:10 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_player(t_map *map, size_t x, size_t y)
{
	return ((map->map_array[y][x] == NORTH || map->map_array[y][x] == WEST
		|| map->map_array[y][x] == SOUTH || map->map_array[y][x] == EAST));
}

void	sanitize_map(t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	player_count;

	y = 0;
	player_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x <= map->width)
		{
			if (is_player(map, x, y))
				player_count++;
			if ((map->map_array[y][x] == SURFACE_PLAYABLE
				|| is_player(map, x, y)) && contacts_void(map, x, y))
				return (werror("Error\nMap not well enclosed."), exit(1));
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (werror("Error\nNumber of players is abnormal."), exit(1));
}
