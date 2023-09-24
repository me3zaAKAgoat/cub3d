/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:23:31 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/24 13:23:39 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	iternary(bool statement, int fexpression, int sexpression)
{
	return (fexpression * statement + sexpression * !statement);
}

double	dternary(bool statement, double fexpression, double sexpression)
{
	return (fexpression * statement + sexpression * !statement);
}