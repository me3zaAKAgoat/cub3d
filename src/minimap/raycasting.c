/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/21 03:44:28 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RAY_LENGTH 5

double normalize_angle(double angle)
{
	angle = fmod(angle , 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

bool	is_facing_up(double angle)
{
	return (angle < 0 || angle > PI);
}

bool	is_facing_down(double angle)
{
	return (!is_facing_up(angle));
}

bool	is_facing_right(double angle)
{
	return (angle > 3 * PI / 2 || angle < PI / 2);
}

bool	is_facing_left(double angle)
{
	return (!is_facing_right(angle));
}

double	horizontal_intersection_distance(t_map_element **map, double x, double y, double ray_angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;
	double final_x;
	double final_y;
	
	yintercept = floor(y);
	yintercept += is_facing_down(ray_angle) * 1;
	xintercept = x + (yintercept - y) / tan(ray_angle);
	ystep = 1;
	ystep *= -1 * is_facing_up(ray_angle) + 1 * !is_facing_up(ray_angle);
	xstep = 1 / tan(ray_angle);
	xstep *= -1 * (is_facing_left(ray_angle) && xstep > 0) + 1 * !(is_facing_left(ray_angle) && xstep > 0);
	xstep *= -1 * (is_facing_right(ray_angle) && xstep < 0) + 1 * !(is_facing_right(ray_angle) && xstep < 0);
	final_x = xintercept;
	final_y = yintercept;
	while (final_x >= 0 && final_x <= 32 && final_y >= 0 && final_y <= 27)
	{
		if (is_wall(map, final_x, final_y - (is_facing_up(ray_angle) ? 0.03125 : 0)))
			return (sqrt(pow(final_x - x, 2) + pow(final_y - y, 2)));
		final_x += xstep;
		final_y += ystep;
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance(t_map_element **map, double x, double y, double ray_angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;
	double final_x;
	double final_y;

	xintercept = floor(x);
	xintercept += is_facing_right(ray_angle) * 1;
	yintercept = y + (xintercept - x) * tan(ray_angle);
	xstep = 1;
	xstep *= -1 * is_facing_left(ray_angle) + 1 * !is_facing_left(ray_angle);
	ystep = 1 * tan(ray_angle);
	ystep *= -1 * (is_facing_up(ray_angle) && ystep > 0) + 1 * !(is_facing_up(ray_angle) && ystep > 0);
	ystep *= -1 * (is_facing_down(ray_angle) && ystep < 0) + 1 * !(is_facing_down(ray_angle) && ystep < 0);
	final_x = xintercept;
	final_y = yintercept;
	while (final_x >= 0 && final_x <= 32 && final_y >= 0 && final_y <= 27)
	{
		if (is_wall(map, final_x - (is_facing_left(ray_angle) ? 0.03125 : 0), final_y))
			return (sqrt(pow(final_x - x, 2) + pow(final_y - y, 2)));
		final_x += xstep;
		final_y += ystep;
	}
	return (INT32_MAX);
}

double	intersection_distance(t_map_element **map, double x, double y, double ray_angle)
{
	double	hdistance;
	double	vdistance;

	ray_angle = normalize_angle(ray_angle);
	hdistance = horizontal_intersection_distance(map, x, y, ray_angle);
	vdistance = vertical_intersection_distance(map, x, y, ray_angle);
	if (hdistance < vdistance)
		return (hdistance);
	return (vdistance);
}

void walls_3D(t_global *data,double distance, int i)
{
    double wall_strip_height;
    double raydistance;
	double distance_projection_plane;
	int wall;
	int wallbottom;
	int wall_top;
	int y;
	
	// clear_image(data);
	raydistance = distance * cos(data->player.viewing_angle - data->player.viewing_angle);
    distance_projection_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
    wall_strip_height = (1/raydistance) * distance_projection_plane;
	wall = (int) wall_strip_height;
    wall_top = (WIN_HEIGHT / 2) - (wall / 2);
	if(wall_top < 0)
		wall_top = 0;
	wallbottom = (WIN_HEIGHT / 2) + (wall / 2);
	if (wallbottom > WIN_HEIGHT)
		wallbottom = WIN_HEIGHT;
	y = wall_top;
	int ADFSFAS = 0;
	while (ADFSFAS < y)
	{
		mlx_put_pixel(data->img, i, ADFSFAS, 0x000000FF);
		ADFSFAS++;
	}
    while (y < wallbottom){
			mlx_put_pixel(data->img, i, y, 0xFF0000FF);
        y++;
    }
	ADFSFAS = wallbottom;
	while (ADFSFAS < WIN_HEIGHT)
	{
		mlx_put_pixel(data->img, i, ADFSFAS, 0x000000FF);
		ADFSFAS++;
	}
}

void	cast_all_rays(t_global *data)
{
	int		i;
	t_ray	ray;

	ray.angle = data->player.viewing_angle - FOV / 2;
	// ray.angle = data->player.viewing_angle;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray.distance = intersection_distance(data->map->map_array, data->player.x, data->player.y, ray.angle);
		// ray.distance = 20;
		bresenham(data->minimap_img,
			(t_point){.x = data->player.x * MINIMAP_UNIT, .y = data->player.y * MINIMAP_UNIT},
			(t_point){.x = (data->player.x + cos(ray.angle) * ray.distance) * MINIMAP_UNIT, .y = (data->player.y + sin(ray.angle) * ray.distance) * MINIMAP_UNIT}, 0xFF0000FF);
		ray.angle += FOV / NUM_RAYS;
		walls_3D(data, ray.distance, i);
		i++;
	}
	
}

