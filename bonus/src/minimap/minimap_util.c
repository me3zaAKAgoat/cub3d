/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:13:50 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 21:24:36 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	map_element_color(t_map_element element)
{
	if (element == WALL)
		return (0x121212FF);
	else if (element == DOOR_CLOSED)
		return (0xf57542FF);
	else if (element == DOOR_OPEN)
		return (0x4bde53FF);
	else if (element == SURFACE_NOT_PLAYABLE)
		return (0xFFFFFF40);
	else if (element == SURFACE_PLAYABLE)
		return (0x7F7F7FFF);
	else
		return (0x0FFFFFFFF);
}

void	player_pixel(mlx_image_t *img, int i, int y, int ym)
{
	mlx_put_pixel(img, i, ym + y, map_element_color(NORTH));
	mlx_put_pixel(img, i, ym - y, map_element_color(NORTH));
}
