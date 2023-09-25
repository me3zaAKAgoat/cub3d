/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:43:21 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/24 15:28:08 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

double	initial_angle(t_map_element element)
{
	if (element == EAST)
		return (0);
	else if (element == NORTH)
		return (3 * M_PI_2);
	else if (element == WEST)
		return (PI);
	else
		return (M_PI_2);
}

char	*skip_wspace(char *str)
{
	while (*str && ft_isspace2(*str))
		str++;
	return (str);
}

void	print_map(t_map_element **map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != HORIZONTAL_TERM)
		{
			printf("%d ", map[y][x]);
			x++;
		}
		puts("");
		y++;
	}
}
