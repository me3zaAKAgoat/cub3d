/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/24 06:53:34 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	wall_color(t_ray ray)
{
	if (!ray.is_facing_up && !ray.hit_vertical)
		return (0x43a34bFF);
	else if (ray.is_facing_up && !ray.hit_vertical)
		return (0x43a34bFF);
	else if (!ray.is_facing_right && ray.hit_vertical)
		return (0x255929FF);
	else if (ray.is_facing_right && ray.hit_vertical)
		return (0x255929FF);
	return (0xFFFFFFFF);
}

void	project_wall(t_global *data, t_ray ray)
{
	double	correct_distance;
	double	distance_to_pplane;
	int		wallbottom;
	int		wall_top;
	int		y;

	correct_distance = ray.distance * \
		cos(data->player.viewing_angle - ray.angle);
	distance_to_pplane = (WIN_WIDTH / 2) / tan(FOV / 2);
	wall_top = (WIN_HEIGHT - (1 / correct_distance) * distance_to_pplane) / 2;
	wallbottom = (WIN_HEIGHT + (1 / correct_distance) * distance_to_pplane) / 2;
	y = 0;
	if (wall_top < 0)
		wall_top = 0;
	if (wallbottom > WIN_HEIGHT)
		wallbottom = WIN_HEIGHT;
	while (y < wall_top)
		mlx_put_pixel(data->game_img, ray.id, y++, data->map->ceil_color);
	while (y < wallbottom)
		mlx_put_pixel(data->game_img, ray.id, y++, wall_color(ray));
	while (y < WIN_HEIGHT)
		mlx_put_pixel(data->game_img, ray.id, y++, data->map->floor_color);
}
