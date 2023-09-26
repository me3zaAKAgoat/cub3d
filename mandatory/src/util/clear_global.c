/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:10 by me3za             #+#    #+#             */
/*   Updated: 2023/09/25 09:40:06 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_global(t_global *data)
{
	int	i;

	mlx_delete_xpm42(data->map->no_file);
	mlx_delete_xpm42(data->map->ea_file);
	mlx_delete_xpm42(data->map->so_file);
	mlx_delete_xpm42(data->map->we_file);
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
