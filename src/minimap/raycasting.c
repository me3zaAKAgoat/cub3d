/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/20 03:24:14 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RAY_LENGTH 5

double normalize_angle(double angle)
{
	return (fmod(angle, 2 * PI));
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

double	horizontal_intersection_distance(t_map_element **map, double x, double y, double ray_angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;
	double final_x;
	double final_y;
	
	yintercept = floor(y);
	yintercept += is_facing_down(ray_angle) * 1;
	
	xintercept = x + (yintercept - y) / tan(ray_angle);
	ystep = 1;
	ystep *= -1 * is_facing_up(ray_angle) + 1 * !is_facing_up(ray_angle);
	xstep = 1 / tan(ray_angle);
	xstep *= -1 * (is_facing_left(ray_angle) && xstep > 0) + 1 * !(is_facing_left(ray_angle) && xstep > 0);
	xstep *= -1 * (is_facing_right(ray_angle) && xstep < 0) + 1 * !(is_facing_right(ray_angle) && xstep < 0);
	final_x = xintercept;
	final_y = yintercept;

	if (is_facing_up(ray_angle))
		final_y -= 0.01;
	while (final_x >= 0 && final_x * MINIMAP_UNIT <= WIN_WIDTH && final_y >= 0 && final_y * MINIMAP_UNIT <= WIN_WIDTH)
	{
		if (is_wall(map, final_x, final_y))
			return (sqrt(pow(final_x - x, 2) + pow(final_y - y, 2)));
		final_x += xstep;
		final_y += ystep;
		printf("%f %f\n", final_x, final_y);
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance(t_map_element **map, double x, double y, double ray_angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;
	double final_x;
	double final_y;

	xintercept = floor(x);
	xintercept += is_facing_right(ray_angle) * 1;
	yintercept = y + (xintercept - x) / tan(ray_angle);
	xstep = 1;
	xstep *= -1 * is_facing_left(ray_angle) + 1 * !is_facing_left(ray_angle);
	ystep = 1 / tan(ray_angle);
	ystep *= -1 * (is_facing_up(ray_angle) && ystep > 0) + 1 * !(is_facing_up(ray_angle) && ystep > 0);
	ystep *= -1 * (is_facing_down(ray_angle) && ystep < 0) + 1 * !(is_facing_down(ray_angle) && ystep < 0);
	final_x = xintercept;
	final_y = yintercept;

	if (is_facing_left(ray_angle))
		final_x -= 0.01;
	while (final_x >= 0 && final_x * MINIMAP_UNIT <= WIN_WIDTH && final_y >= 0 && final_y * MINIMAP_UNIT <= WIN_WIDTH)
	{
		if (is_wall(map, final_x, final_y))
			return (sqrt(pow(final_x - x, 2) + pow(final_y - y, 2)));
		final_x += xstep;
		final_y += ystep;
		printf("%f %f\n", final_x, final_y);
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

void	cast_all_rays(t_global *data)
{
	int		i;
	t_ray	ray;

	// ray.angle = normalize_angle(data->player.viewing_angle - FOV / 2);
	ray.angle = normalize_angle(data->player.viewing_angle);
	i = 0;
	while (i < 1)
	{
		ray.distance = intersection_distance(data->map->map_array, data->player.x, data->player.y, ray.angle);
		// ray.distance = 20;
		printf("%f\n", ray.distance);
		bresenham(data->minimap_img,
			(t_point){.x = data->player.x * MINIMAP_UNIT, .y = data->player.y * MINIMAP_UNIT},
			(t_point){.x = (data->player.x + cos(ray.angle) * ray.distance) * MINIMAP_UNIT, .y = (data->player.y + sin(ray.angle) * ray.distance) * MINIMAP_UNIT}, 0xFF0000FF);
		ray.angle += FOV / NUM_RAYS;
		ray.angle = normalize_angle(ray.angle);
		i++;
	}
}