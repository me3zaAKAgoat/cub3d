/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:44:22 by selhilal          #+#    #+#             */
/*   Updated: 2023/10/01 14:32:28 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    init_sprite(t_global *data)
{
    data->i = 0;
    data->sprite[0] = mlx_load_png("assets/withoutbg/1.png");
    data->sprite[1] = mlx_load_png("assets/withoutbg/2.png");
    data->sprite[2] = mlx_load_png("assets/withoutbg/3.png");
    data->sprite[3] = mlx_load_png("assets/withoutbg/4.png");
}
