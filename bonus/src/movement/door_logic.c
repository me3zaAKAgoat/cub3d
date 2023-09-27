/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:34:39 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/27 21:41:54 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Yes kms indeed means I will kill myself for this code duplication, thank you kind reader :D 
	I will gladely duplicate rather than use flags to change a functions behaviour :D */

bool	is_wall_kms(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL || map->map_array[(int)floor(y)][(int)floor(x)] == SURFACE_NOT_PLAYABLE
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_CLOSED || map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_OPEN)
		return (1);
	return (0);
}

double	horizontal_intersection_distance_kms(t_map *map,
	double x, double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;
	double			tan_ra;

	tan_ra = tan(ray->angle);
	intercept.y = floor(y);
	intercept.y += iternary(!ray->is_facing_up, 1, 0);
	intercept.x = x + (intercept.y - y) / tan_ra;
	step.y = 1;
	step.y *= iternary(ray->is_facing_up, -1, 1);
	step.x = 1 / tan_ra;
	step.x *= iternary(!ray->is_facing_right && step.x > 0, -1, 1);
	step.x *= iternary(ray->is_facing_right && step.x < 0, -1, 1);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width && final.y >= 0 && final.y <= map->height)
	{
		if (is_wall_kms(map, final.x, final.y - dternary(ray->is_facing_up, 0.03125, 0)))
			return (ray->wall_hit_horizontal.x = final.x, ray->wall_hit_horizontal.y = final.y, sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance_kms(t_map *map, double x, double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;
	double			tan_ra;

	tan_ra = tan(ray->angle);
	intercept.x = floor(x);
	intercept.x += iternary(ray->is_facing_right, 1, 0);
	intercept.y = y + (intercept.x - x) * tan_ra;
	step.x = 1;
	step.x *= iternary(!ray->is_facing_right, -1, 1);
	step.y = 1 * tan_ra;
	step.y *= iternary(ray->is_facing_up && step.y > 0, -1, 1);
	step.y *= iternary(!ray->is_facing_up && step.y < 0, -1, 1);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width && final.y >= 0 && final.y <= map->height)
	{
		if (is_wall_kms(map, final.x - dternary(!ray->is_facing_right, 0.03125, 0), final.y))
			return (ray->wall_hit_vertical.x = final.x, ray->wall_hit_vertical.y = final.y, sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

double	intersection_distance_kms(t_map *map, double x, double y, t_ray *ray)
{
	double	hdistance;
	double	vdistance;

	hdistance = horizontal_intersection_distance_kms(map, x, y, ray);
	vdistance = vertical_intersection_distance_kms(map, x, y, ray);
	if (hdistance < vdistance)
		return (ray->hit_vertical = false, hdistance);
	return (ray->hit_vertical = true, vdistance);
}