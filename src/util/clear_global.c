/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:10 by me3za             #+#    #+#             */
/*   Updated: 2023/09/23 03:54:37 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_global(t_global *data)
{
	int	i;

	free(data->map->no_path);
	free(data->map->ea_path);
	free(data->map->so_path);
	free(data->map->we_path);
	if (data->map->map_array)
	{
		i = 0;
		while (data->map->map_array[i])
		{
			free(data->map->map_array[i]);
			i++;
		}
		free(data->map->map_array);
	}
	if (data->mlx)
		mlx_terminate(data->mlx);
}
