/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:25:57 by me3za             #+#    #+#             */
/*   Updated: 2023/09/11 22:45:50 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42.h"
#include <math.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "linked_list.h"

/* Types */

typedef struct s_rgba
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char a;
} t_rgba;

typedef struct s_map
{
    char *NO_path;
    char *SO_path;
    char *EA_path;
    char *WE_path;
    t_rgba floor_color;
    t_rgba ceil_color;
    char **map_info;
} t_map;

typedef struct s_player
{
    double player_angle;
} t_player;

typedef struct s_global
{
    t_map *map;
    t_player player;
} t_global;

/* Function Definitions */

extern size_t strarr_len(char **arr);
extern void werror(char *msg);
extern int ft_isspace(char c);
extern int **parse_map(t_global data, char *filename);

#endif