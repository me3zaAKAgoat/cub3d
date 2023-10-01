/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 17:28:16 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_movement_key_down(t_global *data)
{
	return (mlx_is_key_down(data->mlx, MLX_KEY_W)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D)
		|| mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT));
}

void	init_steps(t_global *data, t_double_couple *fs_step, \
t_double_couple *lr_step)
{
	fs_step->x = MOVE_SPEED * cos(data->player.viewing_angle);
	fs_step->y = MOVE_SPEED * sin(data->player.viewing_angle);
	lr_step->x = MOVE_SPEED * cos(data->player.viewing_angle + M_PI_2);
	lr_step->y = MOVE_SPEED * sin(data->player.viewing_angle + M_PI_2);
}

void	update_movement(t_global *data, t_double_couple *fs_step, \
t_double_couple *lr_step)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.viewing_angle -= ROTATION_SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.viewing_angle += ROTATION_SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)
		&& !hitbox_compromised(data, data->player.viewing_angle))
		move_fb(data, fs_step, true);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		&& !hitbox_compromised(data, data->player.viewing_angle + M_PI))
		move_fb(data, fs_step, false);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)
		&& !hitbox_compromised(data, data->player.viewing_angle + M_PI_2))
		move_lr(data, lr_step, true);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)
		&& !hitbox_compromised(data, data->player.viewing_angle - M_PI_2))
		move_lr(data, lr_step, false);
}

void	move_player(void *param)
{
	t_global			*data;
	t_double_couple		fs_step;
	t_double_couple		lr_step;

	data = param;
	init_steps(data, &fs_step, &lr_step);
	if (is_movement_key_down(data))
		update_movement(data, &fs_step, &lr_step);
	render_game(data);
}
