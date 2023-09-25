/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:16:33 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/25 21:59:00 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_global *data)
{
	if (data->map->map_array[(int)data->player.y + 1][(int)data->player.x] == DOOR)
		data->map->map_array[(int)data->player.y + 1][(int)data->player.x] = door_open;
	if (data->map->map_array[(int)data->player.y - 1][(int)data->player.x] == DOOR)
		data->map->map_array[(int)data->player.y - 1][(int)data->player.x] = door_open;
	if (data->map->map_array[(int)data->player.y][(int)data->player.x + 1] == DOOR)
		data->map->map_array[(int)data->player.y][(int)data->player.x + 1] = door_open;
	if (data->map->map_array[(int)data->player.y][(int)data->player.x - 1] == DOOR)
		data->map->map_array[(int)data->player.y][(int)data->player.x - 1] = door_open;
    data->is_door = 0;
}

void	close_door(t_global *data)
{
	if (data->map->map_array[(int)data->player.y + 1][(int)data->player.x] == door_open)
		data->map->map_array[(int)data->player.y + 1][(int)data->player.x] = DOOR;
	if (data->map->map_array[(int)data->player.y - 1][(int)data->player.x] == door_open)
		data->map->map_array[(int)data->player.y - 1][(int)data->player.x] = DOOR;
	if (data->map->map_array[(int)data->player.y][(int)data->player.x + 1] == door_open)
		data->map->map_array[(int)data->player.y][(int)data->player.x + 1] = DOOR;
	if (data->map->map_array[(int)data->player.y][(int)data->player.x - 1] == door_open)
		data->map->map_array[(int)data->player.y][(int)data->player.x - 1] = DOOR;
    data->is_door = 1;
}


void ft_door(t_global *data, int flag)
{
    (void) flag;
	if (data->map->map_array[(int)data->player.y + 1][(int)data->player.x] == DOOR || \
	data->map->map_array[(int)data->player.y - 1][(int)data->player.x] == DOOR || \
	data->map->map_array[(int)data->player.y][(int)data->player.x + 1] == DOOR || \
	data->map->map_array[(int)data->player.y][(int)data->player.x - 1] == DOOR)
		open_door(data);
	else if (data->map->map_array[(int)data->player.y + 1][(int)data->player.x] == door_open || \
	data->map->map_array[(int)data->player.y - 1][(int)data->player.x] == door_open || \
	data->map->map_array[(int)data->player.y][(int)data->player.x + 1] == door_open || \
	data->map->map_array[(int)data->player.y][(int)data->player.x - 1] == door_open)
		close_door(data);
	
}