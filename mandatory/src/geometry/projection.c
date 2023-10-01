/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 16:57:55 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

xpm_t	*decide_texture(t_global *data, t_ray *ray)
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
	r = xpm_file->texture.pixels[pixel_index \
	* xpm_file->texture.bytes_per_pixel];
	g = xpm_file->texture.pixels[pixel_index \
	* xpm_file->texture.bytes_per_pixel + 1];
	b = xpm_file->texture.pixels[pixel_index \
	* xpm_file->texture.bytes_per_pixel + 2];
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	paint_surfaces(t_global *data, t_ray *ray, t_wall_data *wall)
{
	int	y;

	y = 0;
	while (y < wall->top)
		mlx_put_pixel(data->game_img, ray->id, y++, data->map->ceil_color);
	y = wall->bottom;
	while (y < WIN_HEIGHT)
		mlx_put_pixel(data->game_img, ray->id, y++, data->map->floor_color);
}

void	initiate_wall_values(t_wall_data *wall, t_distance *distance)
{
	wall->top = (WIN_HEIGHT - (1 / distance->no_fishbowl) \
	* distance->to_projection_plane) / 2;
	wall->bottom = (WIN_HEIGHT + (1 / distance->no_fishbowl) \
	* distance->to_projection_plane) / 2;
	wall->strip_height = wall->bottom - wall->top;
	wall->top = iternary(wall->top < 0, 0, wall->top);
	wall->bottom = iternary(wall->bottom > WIN_HEIGHT, \
	WIN_HEIGHT, wall->bottom);
}

void	project_ray(t_global *data, t_ray *ray)
{
	t_distance	distance;
	t_wall_data	wall;
	t_point		offset;
	xpm_t		*xpm_file;

	xpm_file = decide_texture(data, ray);
	distance.no_fishbowl = ray->distance * \
		cos(data->player.viewing_angle - ray->angle);
	distance.to_projection_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
	initiate_wall_values(&wall, &distance);
	paint_surfaces(data, ray, &wall);
	offset.x = iternary(ray->hit_vertical, \
		(int)(ray->wall_hit_y * xpm_file->texture.width) \
		% xpm_file->texture.width, (int)(ray->wall_hit_x * \
		xpm_file->texture.width) % xpm_file->texture.width);
	while (wall.top < wall.bottom)
	{
		distance.from_top = wall.top + ((wall.strip_height) - WIN_HEIGHT) / 2;
		offset.y = (double)(distance.from_top * xpm_file->texture.height) / \
		(double)(wall.strip_height);
		mlx_put_pixel(data->game_img, ray->id, wall.top, extract_color(\
		xpm_file, offset.x, offset.y));
		wall.top++;
	}
}
