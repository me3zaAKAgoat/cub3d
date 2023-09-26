/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:17:48 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/23 18:34:35 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
unsigned is cast for the event that a difference between 
two signed chars is bigger than 128 or smaller than -128
say one chars ascii is 122 and the other is -30
the difference would result in 153 which is bigger than 
the max of unsigned char thus the result wi
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char) s1[i] - (unsigned char)s2[i]);
}
