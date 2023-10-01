/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:53:21 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 20:33:50 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

size_t	strarr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
