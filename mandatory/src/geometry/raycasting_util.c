/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:59:43 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 17:00:23 by echoukri         ###   ########.fr       */
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