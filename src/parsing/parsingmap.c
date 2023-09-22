/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:02:05 by selhilal          #+#    #+#             */
/*   Updated: 2023/09/22 23:44:16 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../includes/cub3d.h"


 int wall_l(t_global *data, int i)
 {
    int j;
    j= 0;

    j = data->map->width;
     while(data->map->map_list[i])
     {
         if( data->map->map_list[i][j] != WALL)
             return (0);
         i++;
     }
     return (1);
 }

 int wall_r(t_global *data, int i)
 {
     if(data->map->map_list[i][0] != WALL)
         return (0);
     return (1);
 }
 int wall_dawn(t_global *data, int i, int j)
 {
    while(data->map->map_list[i][j] != HORIZONTAL_TERM)
    {
        if(data->map->map_list[i + 1][j] != WALL || data->map->map_list[i + 1][j] == HORIZONTAL_TERM)
            return (0);
        j++;
    }
    return (1);
 }

void    parsing_wall(t_global *data)
{
   size_t i;
   size_t j;
   int p;
   p = 0;
   i = 1;
   j = 0;
   while(data->map->map_list[0][j] && data->map->map_list[0][j] != HORIZONTAL_TERM)
   {
       if(data->map->map_list[0][j] != WALL && data->map->map_list[0][j] != SURFACE_NOT_PLAYABLE && data->map->map_list[0][j] != HORIZONTAL_TERM)
       {
        printf("-%zu||-%d\n",j, data->map->map_list[0][j]);
          // werror("Error\n1Map is not closed.");
          // exit(1);
       }
       j++;
   }
   while(data->map->map_list[i])
   {
    
       j = 0;
       while (data->map->map_list[i][j] != HORIZONTAL_TERM)
       {
           if (data->map->map_list[i][j] == SURFACE_PLAYABLE)
           {
               if(!wall_r(data, i) || !wall_l(data, i))
               {
                printf("-%zu||-%zu|-%d\n",i,j,data->map->map_list[i][j]);
                   werror("Error\n2Map is not closed.");
                   exit(1);
               }
               if(data->map->map_list[i][j] == 'P')
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