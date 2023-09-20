/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/19 19:57:05 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RAY_LENGTH 2

double normalize_angle(ray_angle)
{
	ray_angle = ray_angle / (2 * PI);
	if(ray_angle < 0)
		ray_angle = (2 * PI) + ray_angle;
return (ray_angle);
}

void cast_all_rays(t_global *data)
{
	int	i;
	double	ray_angle;

	ray_angle = data->player.viewing_angle - FOV / 2;
	ray_angle = normalize_angle(ray_angle);
	i = 0;
	while (i < NUM_RAYS)
	{
		bresenham(data->minimap_img,
			(t_point){.x = data->player.x * MINIMAP_UNIT, .y = data->player.y * MINIMAP_UNIT},
			(t_point){.x = (data->player.x + cos(ray_angle) * RAY_LENGTH) * MINIMAP_UNIT, .y = (data->player.y + sin(ray_angle) * RAY_LENGTH) * MINIMAP_UNIT}, 0xFF0000FF);
		ray_angle += FOV / NUM_RAYS;
		i++;
	}
	
}

