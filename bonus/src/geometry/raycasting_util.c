/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:03:22 by me3za             #+#    #+#             */
/*   Updated: 2023/09/29 15:54:49 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
