/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:44:29 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/22 16:23:50 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(t_map_element **map, double x, double y)
{
	vertical_len(map);
	if (x < 0 || y < 0)
		return (1);
	if (map[(int)floor(y)][(int)floor(x)] != SURFACE_PLAYABLE)
		return (1);
	return (0);
}

void	move_player(void *param)
{
	t_global	*data;

	data = param;
		if (mlx_is_key_down(data->mlx,MLX_KEY_LEFT))
			data->player.viewing_angle -= ROTATION_SPEED;
		if (mlx_is_key_down (data->mlx,MLX_KEY_RIGHT))
			data->player.viewing_angle += ROTATION_SPEED;
		if (mlx_is_key_down (data->mlx,MLX_KEY_W)
			&& !is_wall(data->map->map_array
			    , data->player.x + MOVE_SPEED * cos(data->player.viewing_angle)
			    , data->player.y + MOVE_SPEED * sin(data->player.viewing_angle)))
		{
			data->player.x += MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y += MOVE_SPEED * sin(data->player.viewing_angle);
		}
		if (mlx_is_key_down(data->mlx,MLX_KEY_S)
			&& !is_wall(data->map->map_array
			    , data->player.x - MOVE_SPEED * cos(data->player.viewing_angle)
			    , data->player.y - MOVE_SPEED * sin(data->player.viewing_angle)))
		{
			data->player.x -= MOVE_SPEED * cos(data->player.viewing_angle);
			data->player.y -= MOVE_SPEED * sin(data->player.viewing_angle);
		}
		if (mlx_is_key_down(data->mlx,MLX_KEY_D)
			&& !is_wall(data->map->map_array
			    , data->player.x + MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2)
			    , data->player.y + MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2)))
		{
			data->player.x += MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2);
			data->player.y += MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2);
		}
		if (mlx_is_key_down(data->mlx,MLX_KEY_A)
			&& !is_wall(data->map->map_array
			    , data->player.x + MOVE_SPEED * cos(data->player.viewing_angle - M_PI_2)
			    , data->player.y + MOVE_SPEED * sin(data->player.viewing_angle - M_PI_2)))
		{
			data->player.x += MOVE_SPEED * cos(data->player.viewing_angle - M_PI_2);
			data->player.y += MOVE_SPEED * sin(data->player.viewing_angle - M_PI_2);
		}
		draw_minimap_background(data);
		cast_all_rays(data);
		player_icon(data, data->player.x * UNIT_SIZE, data->player.y * UNIT_SIZE, PLAYER_CIRCLE, map_element_color(NORTH));
	// }
}