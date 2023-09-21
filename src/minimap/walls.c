/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:48:39 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/21 18:26:40 by selhilal         ###   ########.fr       */
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

#include "cub3d.h"

void walls_3D(t_global *data,double distance, int i)
{
    double wall_strip_height;
	t_ray	ray;
	t_player player;
    double raydistance;
	double distance_projection_plane;
	int wall;
	int wallbottom;
	int wall_top;
	int y;

	raydistance = distance * cos( ray.angle - player.viewing_angle);
    distance_projection_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
    wall_strip_height = (1/raydistance) * distance_projection_plane;
	wall = (int) wall_strip_height;
    wall_top = (WIN_HEIGHT / 2) - (wall / 2);
	if(wall_top < 0)
		wall_top = 0;
	wallbottom = (WIN_HEIGHT / 2) + (wall / 2);
	if (wallbottom > WIN_HEIGHT)
		wallbottom = WIN_HEIGHT;
	int color = 0;
	if (data->map->is_hit_vertical == 1 && is_facing_up(data->player.viewing_angle))
		color = 0xFF0000FF;
	else if (data->map->is_hit_vertical == 1 && is_facing_down(data->player.viewing_angle))
		color = 0x00FF00FF;
	else if (data->map->is_hit_vertical == 0 && is_facing_left(data->player.viewing_angle))
		color = 0x0000FFFF;
	else if (data->map->is_hit_vertical == 0 && is_facing_right(data->player.viewing_angle))
		color = 0xFFFF00FF;
	y = wall_top;
	int ADFSFAS = 0;
	while (ADFSFAS < wall_top && ADFSFAS < WIN_HEIGHT / 2)
	{
		mlx_put_pixel(data->img, i, ADFSFAS, ft_pixel(data->map->ceil_color.red, data->map->ceil_color.green, data->map->ceil_color.blue,255));
		ADFSFAS++;
	}
    while (y < wallbottom){
		mlx_put_pixel(data->img, i, y, color);
        y++;
    }
	ADFSFAS = wallbottom;
	while (ADFSFAS < WIN_HEIGHT && ADFSFAS >= WIN_HEIGHT / 2)
	{
		mlx_put_pixel(data->img, i, ADFSFAS, ft_pixel(data->map->floor_color.red, data->map->floor_color.green, data->map->floor_color.blue,255));
		ADFSFAS++;
	}
}

