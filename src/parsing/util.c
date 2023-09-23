/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:43:21 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/23 18:28:46 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double initial_angle(t_map_element element)
{
	if (element == EAST)
		return (0);
	else if (element == NORTH)
		return (PI * 1.5);
	else if (element == WEST)
		return (PI);
	else
		return (PI * .5);
}

char	*skip_wspace(char *str)
{
	if (!str)
		return (NULL);
	while (*str && ft_isspace2(*str))
		str++;
	return (str);
}

void	print_map(t_map_element **map)
{
	size_t  y;
	size_t  x;

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
