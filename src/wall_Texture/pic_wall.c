/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:50:58 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/24 17:52:35 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void wall_png(t_global *data)
{
    //mlx_texture_t* mlx_load_png(const char* path);
    //void mlx_delete_xpm42(xpm_t* xpm);
    //mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);
	uint32_t		 *texture;
	mlx_texture_t	*tere;
	uint32_t		*wall_texture;
	uint32_t		x;
	uint32_t 	y;
	
	x = 0;
	y = 0;
	texture = (uint32_t *)malloc(sizeof(uint32_t)* WIN_WIDTH * WIN_HEIGHT);
	tere = mlx_load_png("./assets/wall.png/wall.png");
	wall_texture =(uint32_t *) malloc(sizeof(uint32_t) * tere->width * tere->height * sizeof(uint32_t)); 
	while(x < tere->width)
	{
		y = 0;
		while(y < tere->height)
		{
            put_pixel(wall_texture, x, y, get_pixel(tere, x, y));
			y++;
		}
		x++;
	}
}