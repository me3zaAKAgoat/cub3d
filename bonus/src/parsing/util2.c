/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:45:55 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 20:46:00 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	color_invalid(char **colors)
{
	return (strarr_len(colors) != 3 \
		|| !(ft_isnumber(colors[0]) \
		&& ft_isnumber(colors[1]) && ft_isnumber(colors[2])));
}
