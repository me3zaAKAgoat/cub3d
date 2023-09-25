/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/25 04:56:14 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	wall_color(t_ray *ray, uint32_t r, uint32_t g, uint32_t b)
{
	if (!ray->is_facing_up && !ray->hit_vertical)
		return ((r << 24 | g << 16 | b << 8 | 255));
	else if (ray->is_facing_up && !ray->hit_vertical)
		return ((r << 24 | g << 16 | b << 8 | 255));
	else if (!ray->is_facing_right && ray->hit_vertical)
		return (((r - 30) << 24 | (g - 30) << 16 | (b - 30) << 8 | 255));
	else if (ray->is_facing_right && ray->hit_vertical)
		return (((r - 30) << 24 | (g - 30) << 16 | (b - 30) << 8 | 255));
	return (0xFFFFFFFF);
}

void	project_wall(t_global *data, t_ray *ray)
{
	double	correct_distance;
	double	distance_to_pplane;
	int		wall_bottom;
	int		wall_top;
	int		y;

	correct_distance = ray->distance * \
		cos(data->player.viewing_angle - ray->angle);
	distance_to_pplane = (WIN_WIDTH / 2) / tan(FOV / 2);
	wall_top = (WIN_HEIGHT - (1 / correct_distance) * distance_to_pplane) / 2;
	wall_bottom = (WIN_HEIGHT + (1 / correct_distance) * distance_to_pplane) / 2;
	int wall_strip_height = wall_bottom - wall_top;
	y = 0;
	wall_top = iternary(wall_top < 0, 0, wall_top);
	wall_bottom = iternary(wall_bottom > WIN_HEIGHT, WIN_HEIGHT, wall_bottom);
	while (y < wall_top)
		mlx_put_pixel(data->game_img, ray->id, y++, data->map->ceil_color);
	int textureOffsetX;
	if (ray->hit_vertical)
		textureOffsetX = (int)(ray->wall_hit_y * data->wallt->texture.width) % data->wallt->texture.width;
	else
		textureOffsetX = (int)(ray->wall_hit_x * data->wallt->texture.width) % data->wallt->texture.width;

	while (y < wall_bottom)
	{
		int		distance_from_top = y + ((wall_strip_height) - WIN_HEIGHT) / 2;
		int		texture_y = (double)(distance_from_top * data->wallt->texture.height) / (double)(wall_strip_height);

		int		pixel_index = texture_y * data->wallt->texture.width + textureOffsetX;
		uint8_t	red = data->wallt->texture.pixels[pixel_index * data->wallt->texture.bytes_per_pixel];
		uint8_t	green = data->wallt->texture.pixels[pixel_index * data->wallt->texture.bytes_per_pixel + 1];
		uint8_t	blue = data->wallt->texture.pixels[pixel_index * data->wallt->texture.bytes_per_pixel + 2];
		mlx_put_pixel(data->game_img, ray->id, y, wall_color(ray, red, green, blue));
		y++;
	}
	while (y < WIN_HEIGHT)
		mlx_put_pixel(data->game_img, ray->id, y++, data->map->floor_color);
}
