/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:05:50 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/12 03:24:38 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_map_defaults(t_map *map)
{
    map->EA_path = NULL;
    map->NO_path = NULL;
    map->SO_path = NULL;
    map->WE_path = NULL;
    map->ceil_color = (t_rgba){.red = 0, .green = 0, .blue = 0};
    map->floor_color = (t_rgba){.red = 0, .green = 0, .blue = 0};
    map->map_array = NULL;
}

int main(int ac, char **av)
{
    t_map map;
    t_global data;

    (void)ac;
    set_map_defaults(&map);
    data.map = &map;
    parse_config_file(data, av[1]);
}