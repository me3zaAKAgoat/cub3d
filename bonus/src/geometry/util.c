/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:41:23 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 15:55:58 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	initiate_wall_values(t_wall_data *wall, t_distance *distance)
{
	wall->top = (WIN_HEIGHT - (1 / distance->no_fishbowl) \
	* distance->to_projection_plane) / 2;
	wall->bottom = (WIN_HEIGHT + (1 / distance->no_fishbowl) \
	* distance->to_projection_plane) / 2;
	wall->strip_height = wall->bottom - wall->top;
	wall->top = iternary(wall->top < 0, 0, wall->top);
	wall->bottom = iternary(wall->bottom > WIN_HEIGHT, \
	WIN_HEIGHT, wall->bottom);
}
