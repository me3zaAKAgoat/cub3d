/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:56:08 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 20:02:18 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	uniform_arrays_width(t_global *data)
{
	size_t	y;
	size_t	x;
	size_t	hlen;

	y = 0;
	while (data->map->map_array[y])
	{
		hlen = horizontal_len(data->map->map_array[y]);
		if (hlen < data->map->width)
		{
			data->map->map_array[y] = ft_realloc(data->map->map_array[y],
					hlen * sizeof(int), (data->map->width + 2) * sizeof(int));
			if (!data->map->map_array[y])
				return (werror("Error\nA heap allocation failed."), exit(1));
			x = hlen;
			while (x <= data->map->width)
			{
				data->map->map_array[y][x] = SURFACE_NOT_PLAYABLE;
				x++;
			}
			data->map->map_array[y][x] = HORIZONTAL_TERM;
		}
		y++;
	}
}

void	initialize_map_array(t_global *data, int y, char *line)
{
	data->map->map_array = ft_realloc(data->map->map_array,
			y * sizeof(int *), (y + 2) * sizeof(int *));
	if (!data->map->map_array)
		return (werror("Error\nA heap allocation failed."), exit(1));
	data->map->map_array[y + 1] = NULL;
	data->map->map_array[y] = malloc((ft_strlen(line)
				+ 1 * (line[ft_strlen(line) - 1] != '\n')) * sizeof(int));
	if (!data->map->map_array[y])
		return (werror("Error\nA heap allocation failed."), exit(1));
}

void	process_map_line(t_global *data, int x, int y, char *line)
{
	while (line[x])
	{
		data->map->map_array[y][x] = char_to_map_element(line[x]);
		if (data->map->map_array[y][x] >= NORTH
			&& data->map->map_array[y][x] <= SOUTH)
		{
			data->player.x = x + .5;
			data->player.y = y + .5;
			data->player.viewing_angle = \
				initial_angle(data->map->map_array[y][x]);
		}
		x++;
	}
	if (line[ft_strlen(line) - 1] != '\n')
		data->map->map_array[y][x] = HORIZONTAL_TERM;
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && !ft_strncmp(skip_wspace(line), "\n", 1))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	parse_map(t_global *data, int fd)
{
	char	*line;
	int		x;
	int		y;

	y = 0;
	line = skip_empty_lines(fd);
	if (!line)
		return (werror("Error\nNo map found."), exit(1));
	while (line != NULL && ft_strncmp(skip_wspace(line), "\n", 1))
	{
		x = 0;
		initialize_map_array(data, y, line);
		process_map_line(data, x, y, line);
		y++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!data->map->map_array)
	{
		werror("Error\nNo map found.");
		exit(1);
	}
}
