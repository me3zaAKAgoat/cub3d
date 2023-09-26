/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:42:48 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/26 21:49:06 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	horizontal_intersection_distance(t_map *map, double x, double y, t_ray *ray)
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
		if (is_wall(map, final.x, final.y - dternary(ray->is_facing_up, 0.03125, 0)))
		{
			ray->wall_hit_x = final.x;
			return (sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		}
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance(t_map *map, double x, double y, t_ray *ray)
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
		if (is_wall(map, final.x - dternary(!ray->is_facing_right, 0.03125, 0), final.y))
		{
			ray->wall_hit_y = final.y;
			return (sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		}	
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
		ray.distance = intersection_distance(data->map, data->player.x, data->player.y, &ray);
		project_ray(data, &ray);
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