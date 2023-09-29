/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:34:39 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/29 13:45:16 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horiz_inter_kms(t_double_couple *step, t_ray *ray, double *tan_ra)
{
	step->y = 1;
	step->y *= iternary(ray->is_facing_up, -1, 1);
	step->x = 1 / *tan_ra;
	step->x *= iternary(!ray->is_facing_right && step->x > 0, -1, 1);
	step->x *= iternary(ray->is_facing_right && step->x < 0, -1, 1);
}

double	horizontal_inter_distance_kms(t_map *map,
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
	horiz_inter_kms(&step, ray, &tan_ra);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width && final.y >= 0 && \
		final.y <= map->height)
	{
		if (is_wall_kms(map, final.x, final.y - dternary(ray->is_facing_up, \
			0.03125, 0)))
			return (ray->hit_hor.x = final.x, \
				ray->hit_hor.y = final.y, sqrt(pow(final.x - x, 2) \
					+ pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

void	vert_inter_kms(t_double_couple *step, t_ray *ray, double *tan_ra)
{
	step->x = 1;
	step->x *= iternary(!ray->is_facing_right, -1, 1);
	step->y = 1 * *tan_ra;
	step->y *= iternary(ray->is_facing_up && step->y > 0, -1, 1);
	step->y *= iternary(!ray->is_facing_up && step->y < 0, -1, 1);
}

double	vertical_inter_distance_kms(t_map *map, double x, double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;
	double			tan_ra;

	tan_ra = tan(ray->angle);
	intercept.x = floor(x);
	intercept.x += iternary(ray->is_facing_right, 1, 0);
	intercept.y = y + (intercept.x - x) * tan_ra;
	vert_inter_kms(&step, ray, &tan_ra);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width && final.y >= 0 && final.y \
		<= map->height)
	{
		if (is_wall_kms(map, final.x - dternary(!ray->is_facing_right, 0.03125, \
			0), final.y))
			return (ray->hit_ver.x = final.x, ray->hit_ver.y
				= final.y, sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

double	intersection_distance_kms(t_map *map, double x, double y, t_ray *ray)
{
	double	hdistance;
	double	vdistance;

	hdistance = horizontal_inter_distance_kms(map, x, y, ray);
	vdistance = vertical_inter_distance_kms(map, x, y, ray);
	if (hdistance < vdistance)
		return (ray->hit_v = false, hdistance);
	return (ray->hit_v = true, vdistance);
}
