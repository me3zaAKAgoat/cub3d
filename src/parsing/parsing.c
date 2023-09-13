/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:34:33 by me3za             #+#    #+#             */
/*   Updated: 2023/09/14 00:15:47 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_wspace(char *str)
{
	while (*str && ft_isspace2(*str))
		str++;
	return (str);
}

int	char_to_map_element(char c)
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

void textures_colors(t_global *data, int fd)
{
	char *line;
	int textures_recognized;
	int surfaces_recognized;

	textures_recognized = 0;
	surfaces_recognized = 0;
	line = get_next_line(fd);
	while (line != NULL && textures_recognized + surfaces_recognized < 6)
	{
		if (!ft_strncmp(skip_wspace(line), "NO", 2))
		{
			if (data->map->NO_path != NULL)
				return (werror("Error\nPath for NO recognized twice."), exit(1));
			textures_recognized++;
			data->map->NO_path = ft_strtrim(skip_wspace(line + 2), "\n");
		}
		else if (!ft_strncmp(skip_wspace(line), "SO", 2))
		{
			if (data->map->SO_path != NULL)
				return (werror("Error\nPath for SO recognized twice."), exit(1));
			textures_recognized++;
			data->map->SO_path = ft_strtrim(skip_wspace(line + 2), "\n");
		}
		else if (!ft_strncmp(skip_wspace(line), "WE", 2))
		{
			if (data->map->WE_path != NULL)
				return (werror("Error\nPath for WE recognized twice."), exit(1));
			textures_recognized++;
			data->map->WE_path = ft_strtrim(skip_wspace(line + 2), "\n");
		}
		else if (!ft_strncmp(skip_wspace(line), "EA", 2))
		{
			if (data->map->EA_path != NULL)
				return (werror("Error\nPath for EA recognized twice."), exit(1));
			textures_recognized++;
			data->map->EA_path = ft_strtrim(skip_wspace(line + 2), "\n");
		}
		else if (!ft_strncmp(skip_wspace(line), "C", 1))
		{
			char *tmp = ft_strtrim(skip_wspace(line + 1), "\n");
			char **colors = ft_split(tmp, ',');
			
			if (!colors || strarr_len(colors) < 3 || !(ft_isnumber(colors[0]) && ft_isnumber(colors[1]) && ft_isnumber(colors[2])))
				return (werror("Error\nCeiling colors invalid."), exit(1));
			data->map->ceil_color.red = ft_atoi(colors[0]);
			data->map->ceil_color.green = ft_atoi(colors[1]);
			data->map->ceil_color.blue = ft_atoi(colors[2]);
			surfaces_recognized++;
			split_clear(colors);
		}
		else if (!ft_strncmp(skip_wspace(line), "F", 1))
		{
			char *tmp = ft_strtrim(skip_wspace(line + 1), "\n");
			char **colors = ft_split(tmp, ',');

			if (!colors || strarr_len(colors) < 3 || !(ft_isnumber(colors[0]) && ft_isnumber(colors[1]) && ft_isnumber(colors[2])))
				return (werror("Error\nFloors colors invalid."), exit(1));
			data->map->floor_color.red = ft_atoi(colors[0]);
			data->map->floor_color.green = ft_atoi(colors[1]);
			data->map->floor_color.blue = ft_atoi(colors[2]);
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
		return (werror("Error\nMissing textures."), exit(1));
	else if (surfaces_recognized < 2)
		return (werror("Error\nMissing surface colors."), exit(1));
}

void	read_map(t_global *data, int fd)
{
	char	*line;
	int		x;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line != NULL && ft_strncmp(skip_wspace(line), "\n", 1))
	{
		x = 0;
		data->map->map_array = ft_realloc(data->map->map_array, y * sizeof(int *), (y + 2) * sizeof(int *));
		data->map->map_array[y + 1] = NULL;
		if (!data->map->map_array)
			return (werror("Error\nA heap allocation failed."), exit(1));
		data->map->map_array[y] = malloc(ft_strlen(line) * sizeof(int));
		if (!data->map->map_array[y])
			return (werror("Error\nA heap allocation failed."), exit(1));
		while (line[x])
		{
			data->map->map_array[y][x] = char_to_map_element(line[x]);
			x++;
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	parse_config_file(t_global *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		werror("Error\nCan't open config file.");
		exit(1);
	}
	textures_colors(data, fd);
	read_map(data, fd);
	close(fd);
}