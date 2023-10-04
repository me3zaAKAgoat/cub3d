/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:34:33 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/04 05:16:20 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <errno.h>

int	parse_ceiling_color(t_global *data, char *line)
{
	char	*tmp;
	char	**colors;
	int		r;
	int		g;
	int		b;

	if (data->map->ceil_color != 0x00000000)
		return (werror("Error\nCeiling color was recognized twice."), \
		exit(1), 0);
	tmp = ft_strtrim(skip_wspace(line + 1), "\n");
	colors = ft_split(tmp, ',');
	if (!colors)
		return (werror("Error\nA heap allocation failed."), exit(1), 0);
	if (count_char(line, ',') > 2 || color_invalid(colors))
		return (free(tmp), split_clear(colors), \
		werror("Error\nCeiling colors invalid."), exit(1), 0);
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0 || errno == EOVERFLOW)
		return (werror("Error\nCeiling colors are out of bound."), exit(1), 0);
	data->map->ceil_color = r << 24 | g << 16 | b << 8 | 255;
	free(tmp);
	split_clear(colors);
	return (1);
}

int	parse_floor_color(t_global *data, char *line)
{
	char	*tmp;
	char	**colors;
	int		r;
	int		g;
	int		b;

	if (data->map->floor_color != 0x00000000)
		return (werror("Error\nFloor color was recognized twice."), exit(1), 0);
	tmp = ft_strtrim(skip_wspace(line + 1), "\n");
	colors = ft_split(tmp, ',');
	if (!colors)
		return (werror("Error\nA heap allocation failed."), exit(1), 0);
	if (count_char(line, ',') > 2 || color_invalid(colors))
		return (free(tmp), split_clear(colors), \
		werror("Error\nFloor colors invalid."), exit(1), 0);
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0 || errno == EOVERFLOW)
		return (werror("Error\nCeiling colors are out of bound."), exit(1), 0);
	data->map->floor_color = r << 24 | g << 16 | b << 8 | 255;
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
	int		assets_recognized;

	assets_recognized = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_texture_line(line))
			assets_recognized += parse_texture(data->map, line);
		else if (!ft_strncmp(skip_wspace(line), "C", 1))
			assets_recognized += parse_ceiling_color(data, line);
		else if (!ft_strncmp(skip_wspace(line), "F", 1))
			assets_recognized += parse_floor_color(data, line);
		else if (ft_strncmp(skip_wspace(line), "\n", 1))
			break ;
		if (assets_recognized == 7)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (assets_recognized < 7)
		return (werror("Error\nMissing assets."), exit(1));
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
	if (extraneous_lines(fd))
		return (werror("Error\nThe map can't be seperated."), exit(1));
	get_map_dimensions(data);
	uniform_arrays_width(data);
	sanitize_map(data->map);
	close(fd);
}
