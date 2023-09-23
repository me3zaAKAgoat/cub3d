/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:24:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/23 15:44:16 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	char	*newptr;

	if (!ptr)
		return (malloc(newsize));
	if (newsize <= oldsize)
		return (ptr);
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}
