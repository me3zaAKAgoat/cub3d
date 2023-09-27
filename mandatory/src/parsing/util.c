/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:58:58 by me3za             #+#    #+#             */
/*   Updated: 2023/09/27 20:24:22 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_texture_line(char *line)
{
	return (!ft_strncmp(skip_wspace(line), "NO", 2)
		|| !ft_strncmp(skip_wspace(line), "SO", 2)
		|| !ft_strncmp(skip_wspace(line), "WE", 2)
		|| !ft_strncmp(skip_wspace(line), "EA", 2));
}

t_map_element	char_to_map_element(char c)
{
	if (c == '1')
		return (WALL);
	else if (c == '0')
		return (SURFACE_PLAYABLE);
	else if (ft_isspace2(c))
		return (SURFACE_NOT_PLAYABLE);
	else if (c == 'N')
		return (NORTH);
	else if (c == 'W')
		return (WEST);
	else if (c == 'E')
		return (EAST);
	else if (c == 'S')
		return (SOUTH);
	else if (c == '\n')
		return (HORIZONTAL_TERM);
	else
	{
		werror("Error\nUnrecognizable map element.");
		exit(1);
	}
}

double	initial_angle(t_map_element element)
{
	if (element == EAST)
		return (0);
	else if (element == NORTH)
		return (3 * M_PI_2);
	else if (element == WEST)
		return (M_PI);
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
