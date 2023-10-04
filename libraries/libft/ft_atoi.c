/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:12:33 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/04 05:14:40 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int	overflows(long long n, int sign, char digit)
{
	return ((sign == 1
			&& (n > (INT_MAX - (digit - '0')) / 10))
		|| (sign == -1
			&& (-n < (INT_MIN + (digit - '0')) / 10)));
}

int	ft_atoi(const char *str)
{
	int			return_number;
	int			i;
	int			sign;

	i = 0;
	return_number = 0;
	sign = 1;
	while ((str[i] <= 13 && 9 <= str[i]) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (overflows(return_number, sign, str[i]))
			errno = EOVERFLOW;
		return_number = return_number * 10 + (str[i++] - 48);
	}
	return (sign * return_number);
}