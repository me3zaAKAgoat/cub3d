/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:02:05 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/19 17:01:35 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t  ft_nbrlen(int *s)
{
    size_t i;

    i = 0;
    while(s[i] != HORIZONTAL_TERM)
        i++;
    return(i);
}

// horizontal
int wall_l(t_global *data, int i, int j)
{
    int k = 0;
    k = ft_nbrlen(data->map->map_array[i]);
    while(data->map->map_array[i][j] < HORIZONTAL_TERM)
    {
        if( data->map->map_array[i][k - 1] != WALL)
            return (0);
        j++;
    }
    return (1);
}

int wall_r(t_global *data, int i)
{
    if(data->map->map_array[i][0] != WALL)
        return (0);
    return (1);
}
int wall_dawn(t_global *data, int i, int j)
{
    while(data->map->map_array[i][j] < HORIZONTAL_TERM)
    {
        if(ft_nbrlen(data->map->map_array[i + 1]) >  ft_nbrlen(data->map->map_array[i]))
        {
            if(data->map->map_array[i + 1][j] == SURFACE_NOT_PLAYABLE)
                return (0);
        }
        j++;
    }
    return (1);
}

 //int wall_up(t_global *data, int i, int j)
 //{
 //       while(i < data->line_height)
 //       {
 //           if()
 //           {
 //               if(i >= 0)
 //               {
 //               if(data->map->map_array[i][j] == SURFACE_NOT_PLAYABLE)
 //                   return (0);
 //               }
 //           }
 //           j++;
 //       }
 //       return (1);
 //}


void    parsing_wall(t_global *data)
{
    size_t i;
    size_t j;
    int p;

    p = 0;
    i = 1;
    j = 0;
    while(data->map->map_array[0][j] && data->map->map_array[0][j] != HORIZONTAL_TERM)
    {
        if(data->map->map_array[0][j] != WALL && data->map->map_array[0][j] != HORIZONTAL_TERM)
        {
            werror("Error\n1Map is not closed.");
            exit(1);
        }
        j++;
    }
    while(data->map->map_array[i])
    {
        
        j = 0;
        while (data->map->map_array[i][j] != HORIZONTAL_TERM)
        {
            if (data->map->map_array[i][j] == SURFACE_PLAYABLE)
            {
                if(!wall_l(data, i, j) || !wall_r(data, i) || !wall_dawn(data, i, j))
                {
                    werror("Error\n2Map is not closed.");
                    exit(1);
                }
                if(data->map->map_array[i][j] == 'P')
                p++;
            }
            j++;
        }
        i++;
    }
    if(p > 1)
    {
        werror("Error\none player");
        exit(1);
    }
}
