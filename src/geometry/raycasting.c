/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/22 22:30:26 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RAY_LENGTH 5

double	horizontal_intersection_distance(t_map *map, double x, double y, double ray_angle)
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
	while (final_x >= 0 && final_x <= map->width && final_y >= 0 && final_y <= map->height)
	{
		if (is_wall(map, final_x, final_y - (is_facing_up(ray_angle) ? 0.03125 : 0)))
			return (sqrt(pow(final_x - x, 2) + pow(final_y - y, 2)));
		final_x += xstep;
		final_y += ystep;
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance(t_map *map, double x, double y, double ray_angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;
	double final_x;
	double final_y;

	xintercept = floor(x);
	xintercept += is_facing_right(ray_angle) * 1;
	yintercept = y + (xintercept - x) * tan(ray_angle);
	xstep = 1;
	xstep *= -1 * is_facing_left(ray_angle) + 1 * !is_facing_left(ray_angle);
	ystep = 1 * tan(ray_angle);
	ystep *= -1 * (is_facing_up(ray_angle) && ystep > 0) + 1 * !(is_facing_up(ray_angle) && ystep > 0);
	ystep *= -1 * (is_facing_down(ray_angle) && ystep < 0) + 1 * !(is_facing_down(ray_angle) && ystep < 0);
	final_x = xintercept;
	final_y = yintercept;
	while (final_x >= 0 && final_x <= map->width && final_y >= 0 && final_y <= map->height)
	{
		if (is_wall(map, final_x - (is_facing_left(ray_angle) ? 0.03125 : 0), final_y))
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

	hdistance = horizontal_intersection_distance(map, x, y, ray->angle);
	vdistance = vertical_intersection_distance(map, x, y, ray->angle);
	if (hdistance < vdistance)
		return (ray->hit_vertical = false, hdistance);
	return (ray->hit_vertical = true, vdistance);
}

void	cast_all_rays(t_global *data)
{
	int		i;
	t_ray	ray;

	ray.angle = normalize_angle(data->player.viewing_angle - FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray.id = i;
		ray.distance = intersection_distance(data->map, data->player.x, data->player.y, &ray);
		bresenham(data->hud_img,
			(t_point){.x = (data->player.x * UNIT_SIZE), .y = (data->player.y * UNIT_SIZE)},
			(t_point){.x = ((data->player.x + cos(ray.angle) * ray.distance) * UNIT_SIZE), .y = ((data->player.y + sin(ray.angle) * ray.distance) * UNIT_SIZE)}, 0xF9DEC9FF);
		project_wall(data, ray);
		ray.angle += FOV / NUM_RAYS;
		ray.angle = normalize_angle(ray.angle);
		i++;
	}
}