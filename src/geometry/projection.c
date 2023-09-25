/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:03:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/25 01:31:46 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	wall_color(t_ray ray)
{
	//(void)ray;
	//uint32_t		 *texture;
	//mlx_texture_t	*tere;
	//uint32_t		*wall_texture;
	//uint32_t		x;
	//uint32_t 	y;
	//
	//x = 0;
	//y = 0;
	//texture = (uint32_t *)malloc(sizeof(uint32_t)* 64 * 64);
	//tere = mlx_load_png("./assets/wall.png");
	//wall_texture =(uint32_t *) malloc(sizeof(uint32_t) * 64 * 64 * sizeof(uint32_t)); 
	//while(x < 64)
	//{
	//	y = 0;
	//	while(y < 64)
	//	{
	//		//texture[0] = tere->pixels[x + y * tere->width];
	//		if(texture[(y * 64) + x] == (x % 8) && (y % 8))
	//			texture[(y * 64) + x] = 0x000000FF;
	//		else
	//			texture[(y * 64) + x] = 0xFFFFFFFF;
	//		y++;
	//	}
	//	x+= 4;
	//}
	if (!ray.is_facing_up && !ray.hit_vertical)
		return (0x43a34bFF);
	else if (ray.is_facing_up && !ray.hit_vertical)
		return (0x43a3FFFF);
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
	//int		disft;
	//int		pr_wallheight;
	//double	offsetx;
	//double	offsety;
	size_t	color = wall_color(ray);
	int		y;

	correct_distance = ray.distance * cos(data->player.viewing_angle - ray.angle);
	distance_to_pplane = (WIN_WIDTH / 2) / tan(FOV / 2);
	wall_top = (WIN_HEIGHT - (1 / correct_distance) * distance_to_pplane) / 2;
	wallbottom = (WIN_HEIGHT + (1 / correct_distance) * distance_to_pplane) / 2;
	//pr_wallheight = wallbottom - wall_top;
	y = 0;
	if (wall_top < 0)
		wall_top = 0;
	if (wallbottom > WIN_HEIGHT)
		wallbottom = WIN_HEIGHT;
	 while (y < wall_top)
	 	mlx_put_pixel(data->game_img, ray.id, y++, data->map->ceil_color);
	//offsetx = data->x % 64;
	while (y < wallbottom && y < WIN_HEIGHT && y >= 0)
	{
		//disft = y + ((wallbottom -wall_top) / 2) - (WIN_HEIGHT / 2);
		//offsety = disft * (64 / pr_wallheight);
		//color = data->tab[(int)(offsety * 64) * 64 + (int)(offsetx * 64)];
		mlx_put_pixel(data->game_img, ray.id,y ,color);
		y++;
	}
	while (y < WIN_HEIGHT)
		mlx_put_pixel(data->game_img, ray.id, y++, data->map->floor_color);
}

