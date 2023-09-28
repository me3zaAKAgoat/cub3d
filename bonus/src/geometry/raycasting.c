/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:39:37 by me3za             #+#    #+#             */
/*   Updated: 2023/09/28 17:36:28 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	horizontal_intersection_distance(t_map *map,
	double x, double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;

	horizontal_intersection_init(&intercept, &step,
		(t_double_couple){.x = x, .y = y}, ray);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width
		&& final.y >= 0 && final.y <= map->height)
	{
		if (is_wall(map,
				final.x, final.y - dternary(ray->is_facing_up, 0.03125, 0)))
			return (ray->wall_hit_horizontal.x = final.x, ray->wall_hit_horizontal.y = final.y,
				sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

double	vertical_intersection_distance(t_map *map, double x,
	double y, t_ray *ray)
{
	t_double_couple	intercept;
	t_double_couple	step;
	t_double_couple	final;

	vertical_intersection_init(&intercept, &step,
		(t_double_couple){.x = x, .y = y}, ray);
	final.x = intercept.x;
	final.y = intercept.y;
	while (final.x >= 0 && final.x <= map->width
		&& final.y >= 0 && final.y <= map->height)
	{
		if (is_wall(map,
				final.x - dternary(!ray->is_facing_right, 0.03125, 0), final.y))
			return (ray->wall_hit_vertical.x = final.x, ray->wall_hit_vertical.y = final.y,
				sqrt(pow(final.x - x, 2) + pow(final.y - y, 2)));
		final.x += step.x;
		final.y += step.y;
	}
	return (INT32_MAX);
}

double	intersection_distance(t_map *map, double x, double y, t_ray *ray)
{
	double	hdistance;
	double	vdistance;

	hdistance = horizontal_intersection_distance(map, x, y, ray);
	vdistance = vertical_intersection_distance(map, x, y, ray);
	if (hdistance < vdistance)
		return (ray->hit_vertical = false, hdistance);
	return (ray->hit_vertical = true, vdistance);
}

void	cast_rays(t_global *data)
{
	t_ray	ray;

	ray.angle = sanitize_angle(data->player.viewing_angle - FOV / 2);
	ray.id = 0;
	while (ray.id < NUM_RAYS)
	{
		ray.is_facing_right = is_facing_right(ray.angle);
		ray.is_facing_up = is_facing_up(ray.angle);
		ray.distance = intersection_distance(data->map,
				data->player.x, data->player.y, &ray);
		project_ray(data, &ray);
		ray.angle += FOV / NUM_RAYS;
		ray.angle = sanitize_angle(ray.angle);
		ray.id++;
	}
}
#include <time.h>

void	render_game(t_global *data)
{
	/* fps logic */
	clock_t start_time, end_time;
	static mlx_image_t *x;
	start_time = clock();
	/* fps logic */
	minimap(data);
	cast_rays(data);
	/* fps logic */
	end_time = clock();
	mlx_delete_image(data->mlx, x);
	double dfps = 1 / ((double)(end_time - start_time) / CLOCKS_PER_SEC);
	char *fps = ft_itoa(dfps);
	x = mlx_put_string(data->mlx, dfps > 300 ? "300" : fps, WIN_WIDTH - 50, 10);
	free(fps);
	/* fps logic */
}
