/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:22:30 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 20:22:55 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_intersection_init(t_double_couple *intercept,
	t_double_couple *step, t_double_couple xy, t_ray *ray)
{
	double	tan_ra;
	double	x;
	double	y;

	x = xy.x;
	y = xy.y;
	tan_ra = tan(ray->angle);
	intercept->y = floor(y);
	intercept->y += iternary(!ray->is_facing_up, 1, 0);
	intercept->x = x + (intercept->y - y) / tan_ra;
	step->y = 1;
	step->y *= iternary(ray->is_facing_up, -1, 1);
	step->x = 1 / tan_ra;
	step->x *= iternary(!ray->is_facing_right && step->x > 0, -1, 1);
	step->x *= iternary(ray->is_facing_right && step->x < 0, -1, 1);
}

double	horizontal_intersection_distance(t_map *map,
	double x, double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;

	horizontal_intersection_init(&intercept, &step,
		(t_double_couple){.x = x, .y = y}, ray);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width
		&& final.y >= 0 && final.y <= map->height)
	{
		if (is_wall(map,
				final.x, final.y - dternary(ray->is_facing_up, 0.03125, 0)))
			return (ray->wall_hit_x = final.x,
				sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}
