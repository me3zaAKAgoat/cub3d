/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:49:18 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/23 20:45:07 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int check_firstline(t_global *data)
{
    size_t i;
    i = 0;
    while(data->map->map_array[0][i] && data->map->map_array[0][i] != HORIZONTAL_TERM)
    {
        if (data->map->map_array[0][i] == WALL ||data->map->map_array[0][i] == SURFACE_NOT_PLAYABLE || data->map->map_array[0][i] == HORIZONTAL_TERM)
            i++;
        else
            return (0);
    }
    return(1);
}

int check_lastline(t_global *data)
{
    size_t i;
    i = 0;
    while(data->map->map_array[data->map->height - 2][i] && data->map->map_array[data->map->height - 2][i] != HORIZONTAL_TERM)
    {
      
        if (data->map->map_array[data->map->height - 2][i] == WALL ||data->map->map_array[data->map->height - 2][i] == SURFACE_NOT_PLAYABLE || data->map->map_array[data->map->height - 2][i] == HORIZONTAL_TERM)
            i++;
        else
            return (0);
    }
    return(1);
}

int check_left(t_global *data)
{
    size_t i;
    i = 0;
    while(data->map->map_array[i][0]  && i < data->map->height && data->map->map_array[i][0] != WALL )
    {
        if (data->map->map_array[i][0] != WALL && data->map->map_array[i][0] != SURFACE_NOT_PLAYABLE)
            return (0);
        i++;
    }
    return(1);
}

int check_right(t_global *data)
{
    size_t i;
    i = 0;
    while( data->map->map_array[i][data->map->width - 1] && i < data->map->map_array[i][data->map->width - 1] && data->map->map_array[i][data->map->width - 1] != WALL)
    {
        if (data->map->map_array[i][data->map->width - 1] != WALL && data->map->map_array[i][data->map->width - 1] != SURFACE_NOT_PLAYABLE)
            return (0);
        i++;
    }
    return(1);
}

int leftthemap(t_global *data, size_t i, size_t j)
{
    while(j >= 0 && data->map->map_array[i][j] != WALL)
    {
        if (data->map->map_array[i][j] == SURFACE_PLAYABLE || data->map->map_array[i][j] == WEST || data->map->map_array[i][j] == EAST || data->map->map_array[i][j] == NORTH || data->map->map_array[i][j] == SOUTH)
            j--;
        else
        {
            puts("upthemap");
            printf("the error %d\n", data->map->map_array[i][j]);
            return (0);
        }
    }
    return (1);
}

int rightthemap(t_global *data, size_t i, size_t j)
{
    while(j < data->map->width && data->map->map_array[i][j] != WALL)
    {
        if (data->map->map_array[i][j] == SURFACE_PLAYABLE || data->map->map_array[i][j] == WEST || data->map->map_array[i][j] == EAST || data->map->map_array[i][j] == NORTH || data->map->map_array[i][j] == SOUTH)
            j++;
         else
        {
            puts("rightthemap");
            return (0);
        }
    }
    return (1);
}

int upthemap(t_global *data, size_t i, size_t j)
{
    while(i >= 0 && data->map->map_array[i][j] != WALL)
    {
        if (data->map->map_array[i][j] == SURFACE_PLAYABLE || data->map->map_array[i][j] == WEST || data->map->map_array[i][j] == EAST || data->map->map_array[i][j] == NORTH || data->map->map_array[i][j] == SOUTH)
            i--;
        else
        {
            puts("upthemap");
            return (0);
        }
    }
    return (1);
}

int downthemap(t_global *data, size_t i, size_t j)
{
    while(i < data->map->height && data->map->map_array[i][j] != WALL)
    {
        if (data->map->map_array[i][j] == SURFACE_PLAYABLE || data->map->map_array[i][j] == WEST || data->map->map_array[i][j] == EAST || data->map->map_array[i][j] == NORTH || data->map->map_array[i][j] == SOUTH)
            i++;
        else
            return (0);
    }
    return (1);
}

void parssing_wall(t_global *data)
{
    size_t i;
    size_t j;
    i = 0;
    j = 0;
    if(!check_firstline(data)|| !check_lastline(data)|| !check_left(data) || !check_right(data))
    {
        werror("Error\n2Map is not closed");
        exit(1);
    }
    i = 1;
   
   if(data->map->map_array[i][j])
   {  
        while(data->map->map_array[i])
        {
            j = 0;
           
           while(data->map->map_array[i][j] != HORIZONTAL_TERM)
           {
               if(data->map->map_array[i][j] != WALL && data->map->map_array[i][j] != SURFACE_NOT_PLAYABLE && data->map->map_array[i][j] != HORIZONTAL_TERM)
               {
                   if(!leftthemap(data,i,j)|| !rightthemap(data,i,j) || !downthemap(data,i,j) || !upthemap(data,i,j))
                   {
                    printf("i = %zu j = %zu\n",i,j);
                       werror("Error\n3 Map is not closed");
                       exit(1);
                   }
               }
               j++;
           }
           i++;
       }
   }
}