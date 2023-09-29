/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:19:29 by me3za             #+#    #+#             */
/*   Updated: 2023/09/29 17:35:42 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define MINIMAP_SIZE 160
# define UNIT_SIZE 6
# define TEXTURE_SIZE 64
# define HITBOX_SIZE .6
# define MINIMAP_OFFSET_X 5
# define MINIMAP_OFFSET_Y 5
# define MOVE_SPEED .2
# define ROTATION_SPEED .06
# define FOV 40 * .01745329251
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS WIN_WIDTH / WALL_STRIP_WIDTH
# define PLAYER_COLOR 0x67E2CBFF

#endif