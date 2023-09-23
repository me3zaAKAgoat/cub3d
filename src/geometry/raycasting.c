/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/23 06:07:12 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RAY_LENGTH 5

double	horizontal_intersection_distance(t_map *map, double x, double y, t_ray *ray)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;
	double final_x;
	double final_y;
	double tan_ra;

	tan_ra = tan(ray->angle);
	yintercept = floor(y);
	yintercept += !ray->is_facing_up * 1;
	xintercept = x + (yintercept - y) / tan_ra;
	ystep = 1;
	ystep *= -1 * ray->is_facing_up + 1 * !ray->is_facing_up;
	xstep = 1 / tan_ra;
	xstep *= -1 * (!ray->is_facing_right && xstep > 0) + 1 * !(!ray->is_facing_right && xstep > 0);
	xstep *= -1 * (ray->is_facing_right && xstep < 0) + 1 * !(ray->is_facing_right && xstep < 0);
	final_x = xintercept;
	final_y = yintercept;
	while (final_x >= 0 && final_x <= map->width && final_y >= 0 && final_y <= map->height)
	{
		if (is_wall(map, final_x, final_y - (ray->is_facing_up ? 0.03125 : 0)))
			return (sqrt(pow(final_x - x, 2) + pow(final_y - y, 2)));
		final_x += xstep;
		final_y += ystep;
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance(t_map *map, double x, double y, t_ray *ray)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;
	double final_x;
	double final_y;
	double tan_ra;

	tan_ra = tan(ray->angle);
	xintercept = floor(x);
	xintercept += ray->is_facing_right * 1;
	yintercept = y + (xintercept - x) * tan_ra;
	xstep = 1;
	xstep *= -1 * !ray->is_facing_right + 1 * !!ray->is_facing_right;
	ystep = 1 * tan_ra;
	ystep *= -1 * (ray->is_facing_up && ystep > 0) + 1 * !(ray->is_facing_up && ystep > 0);
	ystep *= -1 * (!ray->is_facing_up && ystep < 0) + 1 * !(!ray->is_facing_up && ystep < 0);
	final_x = xintercept;
	final_y = yintercept;
	while (final_x >= 0 && final_x <= map->width && final_y >= 0 && final_y <= map->height)
	{
		if (is_wall(map, final_x - (!ray->is_facing_right ? 0.03125 : 0), final_y))
			return (sqrt(pow(final_x - x, 2) + pow(final_y - y, 2)));
		final_x += xstep;
		final_y += ystep;
	}
	return (INT32_MAX);
}

double	intersection_distance(t_map *map, double x, double y, t_ray *ray)
{
	double	hdistance;
	double	vdistance;

	hdistance = horizontal_intersection_distance(map, x, y, ray);
	vdistance = vertical_intersection_distance(map, x, y, ray);
	if (hdistance < vdistance)
		return (ray->hit_vertical = false, hdistance);
	return (ray->hit_vertical = true, vdistance);
}

void	cast_rays(t_global *data)
{
	t_ray	ray;

	ray.angle = sanitize_angle(data->player.viewing_angle - FOV / 2);
	ray.id = 0;
	while (ray.id < NUM_RAYS)
	{
		ray.is_facing_right = is_facing_right(ray.angle);
		ray.is_facing_up = is_facing_up(ray.angle);
		ray.distance = intersection_distance(data->map, data->player.x, data->player.y, &ray);
		project_wall(data, ray);
		ray.angle += FOV / NUM_RAYS;
		ray.angle = sanitize_angle(ray.angle);
		ray.id++;
	}
}

void	render_game(t_global *data)
{
	cast_rays(data);
	minimap(data);
}