/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:41:26 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 21:41:29 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_door(t_global *data, t_ray *ray)
{
	if (ray->hit_vertical
		&& data->map->map_array[(int)floor(ray->wall_hit_y.y)]
		[(int)floor(ray->wall_hit_y.x + \
		iternary(!ray->is_facing_right, -1, 0))] == DOOR_CLOSED)
		return (true);
	else if (!ray->hit_vertical
		&& data->map->map_array[(int)floor(ray->wall_hit_x.y + \
		iternary(ray->is_facing_up, -1, 0))]
		[(int)floor(ray->wall_hit_x.x)] == DOOR_CLOSED)
		return (true);
	return (false);
}

xpm_t	*decide_texture(t_global *data, t_ray *ray)
{
	if (is_door(data, ray))
		return (data->map->door_file);
	if (!ray->is_facing_up && !ray->hit_vertical)
		return (data->map->so_file);
	else if (ray->is_facing_up && !ray->hit_vertical)
		return (data->map->no_file);
	else if (!ray->is_facing_right && ray->hit_vertical)
		return (data->map->we_file);
	else if (ray->is_facing_right && ray->hit_vertical)
		return (data->map->ea_file);
	return (NULL);
}
