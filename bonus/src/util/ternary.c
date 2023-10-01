/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:44:33 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/29 15:54:49 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	iternary(bool statement, int fexpression, int sexpression)
{
	return (fexpression * statement + sexpression * !statement);
}

double	dternary(bool statement, double fexpression, double sexpression)
{
	return (fexpression * statement + sexpression * !statement);
}
