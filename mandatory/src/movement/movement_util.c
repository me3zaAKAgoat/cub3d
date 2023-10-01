/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:34:30 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 17:37:29 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_steps(t_global *data, t_double_couple *fs_step, \
t_double_couple *lr_step)
{
	fs_step->x = MOVE_SPEED * cos(data->player.viewing_angle);
	fs_step->y = MOVE_SPEED * sin(data->player.viewing_angle);
	lr_step->x = MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2);
	lr_step->y = MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2);
}

void	move_fb(t_global *data, t_double_couple *fs_step, bool forward)
{
	if (forward)
	{
		data->player.x += fs_step->x;
		data->player.y += fs_step->y;
	}
	else
	{
		data->player.x -= fs_step->x;
		data->player.y -= fs_step->y;
	}
}

void	move_lr(t_global *data, t_double_couple *lr_step, bool right)
{
	if (right)
	{
		data->player.x += lr_step->x;
		data->player.y += lr_step->y;
	}
	else
	{
		data->player.x -= lr_step->x;
		data->player.y -= lr_step->y;
	}
}
