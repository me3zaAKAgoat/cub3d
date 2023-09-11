/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:34:33 by me3za             #+#    #+#             */
/*   Updated: 2023/09/11 22:46:10 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count_lines(int fd)
{
	int line_count;

	line_count = 0;
	while (get_next_line(fd) != NULL)
		line_count++;
	return (line_count);
}

char *skip_wspace(char *str)
{
	while (*str && ft_isspace(str))
		str++;
	return (str);
}

void textures_colors(t_global data, int fd)
{
	char *line;
	int textures_recognized;
	int surfaces_recognized;

	textures_recognized = 0;
	surfaces_recognized = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!ft_strncmp(skip_wspace(line), "NO", 2))
		{
			if (data.map->NO_path != NULL)
				return (werror("Error\nPath for NO recognized twice!"), exit(1));
			textures_recognized++;
			data.map->NO_path = ft_strdup(skip_wspace(line) + 2);
		}
		else if (!ft_strncmp(skip_wspace(line), "SO", 2))
		{
			if (data.map->SO_path != NULL)
				return (werror("Error\nPath for SO recognized twice!"), exit(1));
			textures_recognized++;
			data.map->SO_path = ft_strdup(skip_wspace(line) + 2);
		}
		else if (!ft_strncmp(skip_wspace(line), "WE", 2))
		{
			if (data.map->WE_path != NULL)
				return (werror("Error\nPath for WE recognized twice!"), exit(1));
			textures_recognized++;
			data.map->WE_path = ft_strdup(skip_wspace(line) + 2);
		}
		else if (!ft_strncmp(skip_wspace(line), "EA", 2))
		{
			if (data.map->EA_path != NULL)
				return (werror("Error\nPath for EA recognized twice!"), exit(1));
			textures_recognized++;
			data.map->EA_path = ft_strdup(skip_wspace(line) + 2);
		}
		else if (!ft_strncmp(skip_wspace(line), "C", 1))
		{
			char *tmp = ft_strdup(skip_wspace(line) + 1);
			char **colors = ft_split(tmp, ',');

			if (!colors || strarr_len(colors) < 3 || !(ft_isdigit(colors[0]) && ft_isdigit(colors[1]) && ft_isdigit(colors[2])))
				return (werror("Error\nCeiling colors invalid"), exit(1));
			data.map->ceil_color.red = ft_atoi(colors[0]);
			data.map->ceil_color.green = ft_atoi(colors[1]);
			data.map->ceil_color.blue = ft_atoi(colors[2]);
			surfaces_recognized++;
			split_clear(colors);
		}
		else if (!ft_strncmp(skip_wspace(line), "F", 1))
		{
			char *tmp = ft_strdup(skip_wspace(line) + 1);
			char **colors = ft_split(tmp, ',');

			if (!colors || strarr_len(colors) < 3 || !(ft_isdigit(colors[0]) && ft_isdigit(colors[1]) && ft_isdigit(colors[2])))
				return (werror("Error\nFloors colors invalid"), exit(1));
			data.map->floor_color.red = ft_atoi(colors[0]);
			data.map->floor_color.green = ft_atoi(colors[1]);
			data.map->floor_color.blue = ft_atoi(colors[2]);
			surfaces_recognized++;
			split_clear(colors);
		}
		else if (ft_strncmp(skip_wspace(line), "\n", 1))
			break;
		free(line);
		line = get_next_line(fd);
	};
	free(line);
	if (textures_recognized < 4)
		return (werror("Error\nMissing textures!"), exit(1));
	else if (surfaces_recognized < 2)
		return (werror("Error\nMissing surface colors!"), exit(1));
}

int **parse_map(t_global data, char *filename)
{
	int fd;
	char **map;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		werror("Error\nCan't open config file!");
		exit(1);
	}
	textures_colors(data, fd);
	data.map->map_info = malloc(count_lines(fd) * sizeof(char *));
	if (!data.map->map_info)
		return (NULL);
	/* read the map */
	close(fd);
}