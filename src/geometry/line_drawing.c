/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:49:21 by me3za             #+#    #+#             */
/*   Updated: 2023/09/22 00:16:28 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_sign(int value)
{
	if (value < 0)
		return (-1);
	if (value > 0)
		return (1);
	return (0);
}

void	check_ex(t_point *current, int *delta, int sign_x, int *err)
{
	if (err[1] > -delta[1])
	{
		err[0] -= delta[1];
		current->x += sign_x;
	}
}

void	check_ey(t_point *current, int *delta, int sign_y, int *err)
{
	if (err[1] < delta[0])
	{
		err[0] += delta[0];
		current->y += sign_y;
	}
}

void	bresenham(mlx_image_t *img, t_point a, t_point b, uint32_t color)
{
	t_point	current;
	int		delta[2];
	int		sign[2];
	int		err[2];

	delta[0] = abs(b.x - a.x);
	delta[1] = abs(b.y - a.y);
	sign[0] = get_sign(b.x - a.x);
	sign[1] = get_sign(b.y - a.y);
	err[0] = delta[0] - delta[1];
	current = a;
	while (current.x != b.x || current.y != b.y)
	{
		mlx_put_pixel(img, current.x, current.y, color);
		err[1] = err[0] * 2;
		check_ex(&current, delta, sign[0], err);
		check_ey(&current, delta, sign[1], err);
	}
}
