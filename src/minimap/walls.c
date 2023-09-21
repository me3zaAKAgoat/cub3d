/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:48:39 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/21 01:23:11 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//A / B =  C / D 
// actual wall height  == 1/  distance to wall== ray_distance  = projected wall height / distance to projection plane == adjacent = opposite / tan(ray_angle) = adjance = window_width / 2/ tan(FOV_ANGLE / 2)
// distanceprojectionplane = (window_width / 2) / tan(FOV_ANGLE / 2)
// var wallstripheight = projected_wall_height = (TILE_SIZE / ray_distance) * distance_to_projection_plane;

// void walls_3D(t_global *data, t_ray ray,int i)
// {
//     double wall_strip_height;
//     double raydistance = ray.distance;
//     double distance_projection_plane = (WIN_WIDTH / 2) / tan(FOV / 2);

//     wall_strip_height = (1/raydistance) * distance_projection_plane;
//     int y = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
// 	int wallbottom = (WIN_HEIGHT / 2) + (wall_strip_height / 2);
// 	if (wallbottom > WIN_HEIGHT)
// 		wallbottom = WIN_HEIGHT;
//     while (y < wallbottom){
//         mlx_put_pixel(data->minimap_img, i, y, 0x00FF00FF);
//         y++;
//     }
// }

