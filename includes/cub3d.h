/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:25:57 by me3za             #+#    #+#             */
/*   Updated: 2023/09/12 19:17:02 by echoukri         ###   ########.fr       */
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

/* Macros */

#define SURFACE_PLAYABLE 0
#define SURFACE_NOT_PLAYABLE 1
#define WALL 2
#define NORTH 3
#define EAST 4
#define WEST 5
#define SOUTH 6
#define HORIZONTAL_TERM 7

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
	int **map_array;
} t_map;

typedef struct s_player
{
	double player_angle;
	double x;
	double y;
} t_player;

typedef struct s_global
{
	t_map *map;
	t_player player;
} t_global;

/* Function Definitions */

extern void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize);
extern size_t	strarr_len(char **arr);
extern void	werror(char *msg);
extern int	ft_isnumber(char *str);
extern int ft_isspace2(char c);
extern void	parse_config_file(t_global *data, char *filename);

#endif