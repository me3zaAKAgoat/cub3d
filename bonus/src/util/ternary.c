/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:44:33 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 20:33:50 by echoukri         ###   ########.fr       */
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
