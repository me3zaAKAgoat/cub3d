/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:53:09 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/25 14:38:15 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

double	sanitize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

bool	is_facing_up(double angle)
{
	return (angle < 0 || angle > PI);
}

bool	is_facing_down(double angle)
{
	return (!is_facing_up(angle));
}

bool	is_facing_right(double angle)
{
	return (angle > 3 * PI / 2 || angle < PI / 2);
}

bool	is_facing_left(double angle)
{
	return (!is_facing_right(angle));
}
