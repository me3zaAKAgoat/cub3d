/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:45:55 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/04 05:04:45 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	color_invalid(char **colors)
{
	return (strarr_len(colors) != 3 \
		|| !(ft_isnumber(colors[0]) \
		&& ft_isnumber(colors[1]) && ft_isnumber(colors[2])));
}

bool	extraneous_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(skip_wspace(line), "\n", 1))
			return (free(line), true);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (false);
}

size_t	count_char(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
