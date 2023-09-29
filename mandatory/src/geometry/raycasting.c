/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/29 22:31:06 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_intersection_init(t_double_couple *intercept,
	t_double_couple *step, t_double_couple xy, t_ray *ray)
{
	double	tan_ra;
	double	x;
	double	y;

	x = xy.x;
	y = xy.y;
	tan_ra = tan(ray->angle);
	intercept->x = floor(x);
	intercept->x += iternary(ray->is_facing_right, 1, 0);
	intercept->y = y + (intercept->x - x) * tan_ra;
	step->x = 1;
	step->x *= iternary(!ray->is_facing_right, -1, 1);
	step->y = 1 * tan_ra;
	step->y *= iternary(ray->is_facing_up && step->y > 0, -1, 1);
	step->y *= iternary(!ray->is_facing_up && step->y < 0, -1, 1);
}

double	vertical_intersection_distance(t_map *map, double x,
	double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;

	vertical_intersection_init(&intercept, &step,
		(t_double_couple){.x = x, .y = y}, ray);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width
		&& final.y >= 0 && final.y <= map->height)
	{
		if (is_wall(map,
				final.x - dternary(!ray->is_facing_right, 0.03125, 0), final.y))
			return (ray->wall_hit_y = final.y,
				sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
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
		ray.distance = intersection_distance(data->map,
				data->player.x, data->player.y, &ray);
		project_ray(data, &ray, 0);
		ray.angle += FOV / NUM_RAYS;
		ray.angle = sanitize_angle(ray.angle);
		ray.id++;
	}
}
