/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:24:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/24 02:19:33 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	char	*newptr;

	if (newsize <= oldsize)
		return (ptr);
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, oldsize);
		free(ptr);
	}
	return (newptr);
}