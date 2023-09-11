/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:05:50 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/11 20:43:55 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_map *map)
{
    map->EA_path = NULL;
    map->NO_path = NULL;
    map->SO_path = NULL;
    map->WE_path = NULL;
    map->ceil_color = NULL;
    map->floor_color = NULL;
    map->map = NULL;
}

int main()
{
    t_map map;
    t_global data;

    data.map = &map;
}