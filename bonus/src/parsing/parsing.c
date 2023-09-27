/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:34:33 by me3za             #+#    #+#             */
/*   Updated: 2023/09/27 16:15:50 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_ceiling_color(t_global *data, char *line)
{
	char	*tmp;
	char	**colors;

	tmp = ft_strtrim(skip_wspace(line + 1), "\n");
	colors = ft_split(tmp, ',');
	if (!colors || strarr_len(colors) < 3
		|| !(ft_isnumber(colors[0])
			&& ft_isnumber(colors[1]) && ft_isnumber(colors[2])))
	{
		free(tmp);
		split_clear(colors);
		return (werror("Error\nCeiling colors invalid."), exit(1), 0);
	}
	data->map->ceil_color = (ft_atoi(colors[0]) << 24)
		| (ft_atoi(colors[1]) << 16) | (ft_atoi(colors[2]) << 8) | 255;
	free(tmp);
	split_clear(colors);
	return (1);
}

int	parse_floor_color(t_global *data, char *line)
{
	char	*tmp;
	char	**colors;

	tmp = ft_strtrim(skip_wspace(line + 1), "\n");
	colors = ft_split(tmp, ',');
	if (!colors || strarr_len(colors) < 3
		|| !(ft_isnumber(colors[0])
			&& ft_isnumber(colors[1]) && ft_isnumber(colors[2])))
	{
		free(tmp);
		split_clear(colors);
		return (werror("Error\nFloors colors invalid."), exit(1), 0);
	}
	data->map->floor_color = (ft_atoi(colors[0]) << 24)
		| (ft_atoi(colors[1]) << 16) | (ft_atoi(colors[2]) << 8) | 255;
	free(tmp);
	split_clear(colors);
	return (1);
}

int	parse_texture(t_map *map, char *line)
{
	xpm_t	**dst;
	char	*str;

	if (!ft_strncmp(skip_wspace(line), "NO", 2))
		dst = &map->no_file;
	else if (!ft_strncmp(skip_wspace(line), "SO", 2))
		dst = &map->so_file;
	else if (!ft_strncmp(skip_wspace(line), "WE", 2))
		dst = &map->we_file;
	else if (!ft_strncmp(skip_wspace(line), "D", 1))
		dst = &map->door_file;
	else
		dst = &map->ea_file;
	if (*dst != NULL)
		return (werror("Error\nA Path was recognized twice."), exit(1), 0);
	str = ft_strtrim(skip_wspace(line + 2), "\n");
	*dst = mlx_load_xpm42(str);
	if (!*dst)
		return (werror("Error\nFailed to load a texture."), exit(1), 0);
	free(str);
	return (1);
}

void	parse_assets(t_global *data, int fd)
{
	char	*line;
	int		textures_recognized;
	int		surfaces_recognized;

	textures_recognized = 0;
	surfaces_recognized = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_texture_line(line))
			textures_recognized += parse_texture(data->map, line);
		else if (!ft_strncmp(skip_wspace(line), "C", 1))
			surfaces_recognized += parse_ceiling_color(data, line);
		else if (!ft_strncmp(skip_wspace(line), "F", 1))
			surfaces_recognized += parse_floor_color(data, line);
		else if (ft_strncmp(skip_wspace(line), "\n", 1)
			|| (textures_recognized == 5 && surfaces_recognized == 2))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (textures_recognized < 5)
		return (werror("Error\nMissing textures."), exit(1));
	else if (surfaces_recognized < 2)
		return (werror("Error\nMissing surface colors."), exit(1));
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
	parse_assets(data, fd);
	parse_map(data, fd);
	get_map_dimensions(data);
	uniform_arrays_width(data);
	sanitize_map(data->map);
	close(fd);
}
