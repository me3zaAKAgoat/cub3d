/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:10 by me3za             #+#    #+#             */
/*   Updated: 2023/09/29 15:54:49 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
