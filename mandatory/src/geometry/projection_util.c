/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:44:04 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 17:33:52 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	handle_fishbowl_effect(t_global *data, t_ray *ray, t_distance *distance)
{
	distance->no_fishbowl = ray->distance * cos(data->player.view_angle \
		- ray->angle);
	return (distance->no_fishbowl);
}
