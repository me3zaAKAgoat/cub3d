/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:52:34 by selhilal          #+#    #+#             */
/*   Updated: 2023/10/01 14:47:54 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		data->player.y -= data->steps.lr_ystep;
	}
	else if (flag == PLUS)
	{
		data->player.x += data->steps.lr_xstep;
		data->player.y += data->steps.lr_ystep;
	}
}

void	move_player_ut(t_global *data)
{
	if (is_movement_key_down(data))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->player.viewing_angle -= ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			data->player.viewing_angle += ROTATION_SPEED;
		if (mlx_is_key_down(data->mlx, MLX_KEY_W) && \
			!hitbox_compromised(data, data->player.viewing_angle))
			key_move_up_down(data, PLUS);
		if (mlx_is_key_down(data->mlx, MLX_KEY_S) && \
			!hitbox_compromised(data, data->player.viewing_angle + M_PI))
			key_move_up_down(data, MINUS);
		if (mlx_is_key_down(data->mlx, MLX_KEY_D) && \
			!hitbox_compromised(data, data->player.viewing_angle + M_PI_2))
			key_move_left_right(data, PLUS);
		if (mlx_is_key_down(data->mlx, MLX_KEY_A) && \
			!hitbox_compromised(data, data->player.viewing_angle - M_PI_2))
			key_move_left_right(data, MINUS);
		if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		{
			mlx_delete_image(data->mlx, data->first);
			data->first = NULL;
		}
	}
	if (data->first != NULL)
	{
		mlx_delete_image(data->mlx, data->first);
		data->first = NULL;
	}
	printf("data->i = %d\n", data->i);
	data->first = mlx_texture_to_image(data->mlx, data->sprite[data->i]);
	if (!data->first)
	{
		werror("mlx texture to image failed.");
		exit(EXIT_FAILURE);
	}
	if(++data->i > 3)
		data->i = 0;
	if(mlx_image_to_window(data->mlx, data->first, 0, 0) <0)
		exit(1);
}