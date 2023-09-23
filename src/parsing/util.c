/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:58:58 by me3za             #+#    #+#             */
/*   Updated: 2023/09/23 04:01:34 by echoukri         ###   ########.fr       */
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