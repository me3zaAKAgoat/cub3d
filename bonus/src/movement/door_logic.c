/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:34:39 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/29 21:01:02 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Yes kms indeed means I will kill
	myself for this code duplication, thank you kind reader :D 
	I will gladely duplicate rather
	than use flags to change a functions behaviour :D */

bool	is_wall_kms(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	if (map->map_array[(int)floor(y)][(int)floor(x)] == WALL
		|| map->map_array[(int)floor(y)][(int)floor(x)] == SURFACE_NOT_PLAYABLE
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_CLOSED
		|| map->map_array[(int)floor(y)][(int)floor(x)] == DOOR_OPEN)
		return (1);
	return (0);
}

double	horizontal_intersection_distance_kms(t_map *map,
	double x, double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;

	horizontal_intersection_init_kms(&intercept, &step,
		(t_double_couple){.x = x, .y = y}, ray);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width
		&& final.y >= 0 && final.y <= map->height)
	{
		if (is_wall_kms(map,
				final.x, final.y - dternary(ray->is_facing_up, 0.03125, 0)))
			return (ray->wall_hit_x.x = final.x,
				ray->wall_hit_x.y = final.y,
				sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance_kms(t_map *map, double x,
	double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;

	vertical_intersection_init_kms(&intercept, &step,
		(t_double_couple){.x = x, .y = y}, ray);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width
		&& final.y >= 0 && final.y <= map->height)
	{
		if (is_wall_kms(map,
				final.x - dternary(!ray->is_facing_right, 0.03125, 0), final.y))
			return (ray->wall_hit_y.x = final.x,
				ray->wall_hit_y.y = final.y,
				sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
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

void	interact_with_door(t_global *data)
{
	t_ray			ray;
	t_map_element	*door;

	ray.angle = sanitize_angle(data->player.viewing_angle);
	ray.is_facing_right = is_facing_right(ray.angle);
	ray.is_facing_up = is_facing_up(ray.angle);
	ray.distance = intersection_distance_kms(data->map,
			data->player.x, data->player.y, &ray);
	if (ray.hit_vertical)
		door = data->map->map_array[(int)ray.wall_hit_y.y]
			+ (int)ray.wall_hit_y.x
			+ iternary(!ray.is_facing_right, -1, 0);
	if (!ray.hit_vertical)
		door = data->map->map_array[(int)ray.wall_hit_x.y
			+ iternary(ray.is_facing_up, -1, 0)]
			+ (int)ray.wall_hit_x.x;
	if (ray.distance < 2)
	{
		if (*door == DOOR_CLOSED)
			*door = DOOR_OPEN;
		else if (*door == DOOR_OPEN)
			*door = DOOR_CLOSED;
	}
}
