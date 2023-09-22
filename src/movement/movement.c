/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/22 02:25:32 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(t_map_element **map, double x, double y)
{
	vertical_len(map);
	if (x < 0 || y < 0)
		return (1);
	if (map[(int)floor(y)][(int)floor(x)] == WALL)
		return (1);
	return (0);
}

// void	event_function(mlx_key_data_t keydata, t_global *data)
// {
	
// }

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_global	*data;

	(void)keydata;
	data = param;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A)
	{
		if (keydata.key == MLX_KEY_A)
			data->player.viewing_angle -= ROTATION_SPEED;
		if (keydata.key == MLX_KEY_D)
			data->player.viewing_angle += ROTATION_SPEED;
		if (keydata.key == MLX_KEY_W
			&& !is_wall(data->map->map_array
			    , data->player.x + MOVE_SPEED * cos(data->player.viewing_angle)
			    , data->player.y + MOVE_SPEED * sin(data->player.viewing_angle)))
		{
			data->player.x += MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y += MOVE_SPEED * sin(data->player.viewing_angle);
		}
		if (keydata.key == MLX_KEY_S
			&& !is_wall(data->map->map_array
			    , data->player.x - MOVE_SPEED * cos(data->player.viewing_angle)
			    , data->player.y - MOVE_SPEED * sin(data->player.viewing_angle)))
		{
			data->player.x -= MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y -= MOVE_SPEED * sin(data->player.viewing_angle);
		}
		draw_minimap_background(data);
		cast_all_rays(data);
		player_icon(data, data->player.x * UNIT_SIZE, data->player.y * UNIT_SIZE, PLAYER_CIRCLE, map_element_color(NORTH));
	}
}