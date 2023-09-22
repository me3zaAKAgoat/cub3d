/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:10 by me3za             #+#    #+#             */
/*   Updated: 2023/09/22 15:46:17 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	clear_global(t_global *data)
{
	int	i;

	free(data->map->no_path);
	free(data->map->ea_path);
	free(data->map->so_path);
	free(data->map->wa_path);
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