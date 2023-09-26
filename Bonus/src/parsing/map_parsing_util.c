/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:14:50 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/26 22:15:20 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	horizontal_len(t_map_element *arr)
{
	size_t	len;

	len = 0;
	while (arr[len] != HORIZONTAL_TERM)
		len++;
	return (len);
}

size_t	vertical_len(t_map_element **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	get_map_dimensions(t_global *data)
{
	size_t	y;	
	size_t	x;

	y = 0;
	while (data->map->map_array[y])
	{
		x = 0;
		while (data->map->map_array[y][x] != HORIZONTAL_TERM)
		{
			if (x > data->map->width)
				data->map->width = x;
			x++;
		}
		y++;
	}
	data->map->height = y;
}