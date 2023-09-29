/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:31:14 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 15:31:22 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vertical_inter(t_double_couple *step, t_ray *ray, double *tan_ra)
{
	step->x = 1;
	step->x *= iternary(!ray->is_facing_right, -1, 1);
	step->y = 1 * *tan_ra;
	step->y *= iternary(ray->is_facing_up && step->y > 0, -1, 1);
	step->y *= iternary(!ray->is_facing_up && step->y < 0, -1, 1);
}

void	init_horizontal_inter(t_double_couple *step, t_ray *ray, double *tan_ra)
{
	step->y = 1;
	step->y *= iternary(ray->is_facing_up, -1, 1);
	step->x = 1 / *tan_ra;
	step->x *= iternary(!ray->is_facing_right && step->x > 0, -1, 1);
	step->x *= iternary(ray->is_facing_right && step->x < 0, -1, 1);
}
