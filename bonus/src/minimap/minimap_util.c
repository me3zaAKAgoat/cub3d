/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:13:50 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/30 13:50:55 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	map_element_color(t_map_element element)
{
	if (element == WALL)
		return (0xe7e6eaFF);
	else if (element == DOOR_CLOSED)
		return (0x434343FF);
	else if (element == DOOR_OPEN)
		return (0x5e575acf);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0x2c2d22FF);
	else if (element == SURFACE_PLAYABLE)
		return (0x81808155);
	else
		return (0x0FFFFFFFF);
}

void	player_pixel(mlx_image_t *img, int i, int y, int ym)
{
	mlx_put_pixel(img, i, ym + y, PLAYER_COLOR);
	mlx_put_pixel(img, i, ym - y, PLAYER_COLOR);
}
