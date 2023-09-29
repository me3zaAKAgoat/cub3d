/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/29 17:32:33 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/29 17:32:05 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

xpm_t	*decide_texture(t_global *data, t_ray *ray)
{
	if (!ray->is_facing_up && !ray->hit_v)
		return (data->map->so_file);
	else if (ray->is_facing_up && !ray->hit_v)
		return (data->map->no_file);
	else if (!ray->is_facing_right && ray->hit_v)
		return (data->map->we_file);
	else if (ray->is_facing_right && ray->hit_v)
		return (data->map->ea_file);
	return (NULL);
}

uint32_t	extract_color(xpm_t *xpm, int x_offset, int y_offset)
{
	int			pixel_index;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	pixel_index = y_offset * xpm->texture.width + x_offset;
	r = xpm->texture.pixels[pixel_index \
	* xpm->texture.bytes_per_pixel];
	g = xpm->texture.pixels[pixel_index \
	* xpm->texture.bytes_per_pixel + 1];
	b = xpm->texture.pixels[pixel_index \
	* xpm->texture.bytes_per_pixel + 2];
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

void	project_ray(t_global *data, t_ray *ray, xpm_t *xpm)
{
	t_distance	distance;
	t_wall_data	wall;
	t_point		offset;

	xpm = decide_texture(data, ray);
	distance.no_fishbowl = handle_fishbowl_effect(data, ray, &distance);
	distance.pp = (WIN_WIDTH / 2) / tan(FOV / 2);
	wall.top = (WIN_HEIGHT - (1 / distance.no_fishbowl) * distance.pp) / 2;
	wall.bottom = (WIN_HEIGHT + (1 / distance.no_fishbowl) * distance.pp) / 2;
	wall.strip_height = wall.bottom - wall.top;
	wall.top = iternary(wall.top < 0, 0, wall.top);
	wall.bottom = iternary(wall.bottom > WIN_HEIGHT, WIN_HEIGHT, wall.bottom);
	paint_surfaces(data, ray, &wall);
	offset.x = iternary(ray->hit_v, (int)(ray->hit_ver.y * xpm->texture.width) \
		% xpm->texture.width, (int)(ray->hit_hor.x * \
			xpm->texture.width) % xpm->texture.width);
	while (wall.top < wall.bottom)
	{
		distance.from_top = wall.top + ((wall.strip_height) - WIN_HEIGHT) / 2;
		offset.y = (double)(distance.from_top * xpm->texture.height) / \
			(double)(wall.strip_height);
		mlx_put_pixel(data->game_img, ray->id, wall.top, \
			extract_color(xpm, offset.x, offset.y));
		wall.top++;
	}
}
