/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:14:38 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/29 18:15:54 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_move_up_down(t_global *data, int flag)
{
	if (flag == PLUS)
	{
		data->player.x += data->steps.fs_xstep;
		data->player.y += data->steps.fs_ystep;
	}
	else if (flag == MINUS)
	{
		data->player.x -= data->steps.fs_xstep;
		data->player.y -= data->steps.fs_ystep;
	}
}

void	key_move_left_right(t_global *data, int flag)
{
	if (flag == MINUS)
	{
		data->player.x -= data->steps.lr_xstep;
		data->player.y -= data->steps.lr_yste;
	}
	else if (flag == PLUS)
	{
		data->player.x += data->steps.lr_xstep;
		data->player.y += data->steps.lr_yste;
	}
}
