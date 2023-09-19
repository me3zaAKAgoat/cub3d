/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/19 03:01:29 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RAY_LENGTH 2

void cast_all_rays(t_global *data)
{
	int	i;
	double	ray_angle;

	ray_angle = data->player.viewing_angle - FOV / 2;
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