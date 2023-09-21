/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/21 20:29:10 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void project_wall(t_global *data, t_ray ray)
{
	int		wall_strip_height;
	double	correct_distance;
	double	distance_to_pplane;
	int		wallbottom;
	int		wall_top;

	correct_distance = ray.distance * cos(data->player.viewing_angle - ray.angle);
	distance_to_pplane = (WIN_WIDTH / 2) / tan(FOV / 2);
	wall_strip_height = (1 / correct_distance) * distance_to_pplane;
	wall_top = (WIN_HEIGHT - wall_strip_height) / 2;
	wallbottom = (WIN_HEIGHT + wall_strip_height) / 2;
	if (wall_top < 0)
		wall_top = 0;
	if (wallbottom > WIN_HEIGHT)
		wallbottom = WIN_HEIGHT;
	int y = 0;
	while (y < wall_top )
		mlx_put_pixel(data->game_img, ray.id, y++, data->map->ceil_color);
	while (y < wallbottom)
			mlx_put_pixel(data->game_img, ray.id, y++, 0xFFFFFFFF);
	while (y < WIN_HEIGHT)
		mlx_put_pixel(data->game_img, ray.id, y++, data->map->floor_color);
}