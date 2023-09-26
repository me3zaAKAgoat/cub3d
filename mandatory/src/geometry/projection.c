/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/26 21:48:46 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

xpm_t		*decide_texture(t_global *data, t_ray *ray)
{
	if (!ray->is_facing_up && !ray->hit_vertical)
		return (data->map->so_file);
	else if (ray->is_facing_up && !ray->hit_vertical)
		return (data->map->no_file);
	else if (!ray->is_facing_right && ray->hit_vertical)
		return (data->map->we_file);
	else if (ray->is_facing_right && ray->hit_vertical)
		return (data->map->ea_file);
	return (NULL);
}

uint32_t	extract_color(xpm_t *xpm_file, int x_offset, int y_offset)
{
	int			pixel_index;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	pixel_index = y_offset * xpm_file->texture.width + x_offset;
	r = xpm_file->texture.pixels[pixel_index * xpm_file->texture.bytes_per_pixel];
	g = xpm_file->texture.pixels[pixel_index * xpm_file->texture.bytes_per_pixel + 1];
	b = xpm_file->texture.pixels[pixel_index * xpm_file->texture.bytes_per_pixel + 2];
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	project_ray(t_global *data, t_ray *ray)
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
	xpm_t	*xpm_file;;
	xpm_file = decide_texture(data, ray);
	int t_offset_x;
	if (ray->hit_vertical)
		t_offset_x = (int)(ray->wall_hit_y * xpm_file->texture.width) % xpm_file->texture.width;
	else
		t_offset_x = (int)(ray->wall_hit_x * xpm_file->texture.width) % xpm_file->texture.width;
	while (y < wall_bottom)
	{
		int		distance_from_top = y + ((wall_strip_height) - WIN_HEIGHT) / 2;
		int		t_offset_y = (double)(distance_from_top * xpm_file->texture.height) / (double)(wall_strip_height);
		mlx_put_pixel(data->game_img, ray->id, y, extract_color(xpm_file, t_offset_x, t_offset_y));
		y++;
	}
	while (y < WIN_HEIGHT)
		mlx_put_pixel(data->game_img, ray->id, y++, data->map->floor_color);
}