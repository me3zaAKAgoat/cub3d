/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/20 14:30:12 by selhilal         ###   ########.fr       */
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

bool	is_facing_up(double angle)
{
	return (angle > 0 && angle < PI);
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
bool	is_wall(t_map_element **map, double x, double y)
{
	if (map[(int)floor(y)][(int)floor(x)] == WALL)
		return (1);
	return (0);
}

double horizonatl_intersection(t_global *data, double rayAngle)
{
	double xintercept;
	double yintercept;
	double ystep;
	double xstep;
	double finlex;
	double finley;

	yintercept = floor(data->player.y / MINIMAP_UNIT) * MINIMAP_UNIT;
	yintercept += is_facing_down(data->player.viewing_angle) ? MINIMAP_UNIT : 0;
	xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);

	ystep = MINIMAP_UNIT;
	ystep *= is_facing_up(data->player.viewing_angle) ? -1 : 1;
	xstep = MINIMAP_UNIT / tan(rayAngle);
	xstep *= (is_facing_left(data->player.viewing_angle) && xstep > 0) ? -1 : 1;
	xstep *= (is_facing_right(data->player.viewing_angle) && xstep < 0) ? -1 : 1;
	finlex = xintercept;
	finley = yintercept;
	if(is_facing_up(data->player.viewing_angle))
		finley--;
	while (finlex >= 0 && finlex * MINIMAP_UNIT <= WIN_WIDTH && finley >= 0 && finley * MINIMAP_UNIT <= WIN_WIDTH)
	{
		if (is_wall(data->map, finlex, finley))
		{
			return (0);
		}
		finlex += xstep;
		finley += ystep;
	}
	return (INT32_MAX);
}

double	intersection_distance(t_map_element **map, double x, double y, double ray_angle)
{
	double	hdistance;
	double	vdistance;

	hdistance = horizontal_intersection_distance(map, x, y, ray_angle);
	vdistance = vertical_intersection_distance(map, x, y, ray_angle);
	if (hdistance < 0)
		return (hdistance);
	return (vdistance);
}

void cast_all_rays(t_global *data)
{
	int	i;
	double	ray_angle;

	ray_angle = data->player.viewing_angle - FOV / 2;
	//ray_angle = normalize_angle(ray_angle);
	horizonatl_intersection(data, ray_angle);
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

