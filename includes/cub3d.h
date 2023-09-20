/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:25:57 by me3za             #+#    #+#             */
/*   Updated: 2023/09/20 16:11:35 by me3za            ###   ########.fr       */
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

#define WIN_WIDTH 1600
#define WIN_HEIGHT 900

/* Minimap */
#define MINIMAP_UNIT 20
#define HITBOX_SIZE 1
#define PLAYER_CIRCLE (MINIMAP_UNIT / 2)
#define OFFSET_X (MINIMAP_UNIT / 2)
#define OFFSET_Y (MINIMAP_UNIT / 2)
#define MINIMAP_MOVE_SPEED .25
#define ROTATION_SPEED .008
/*        */

#define FOV_DEG 90
#define PI 3.14159265359
#define PI_BY_ONEEIGHTY 0.01745329251
#define FOV FOV_DEG * PI_BY_ONEEIGHTY
#define WALL_STRIP_WIDTH 1
#define NUM_RAYS WIN_WIDTH / WALL_STRIP_WIDTH

/* Types */

typedef enum e_map_element 
{
	SURFACE_PLAYABLE,
	SURFACE_NOT_PLAYABLE,
	WALL,
	NORTH,
	EAST,
	WEST,
	SOUTH,
	HORIZONTAL_TERM
} t_map_element;

typedef struct s_rgba
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	a;
} t_rgba;

typedef struct s_map
{
	char				*NO_path;
	char				*SO_path;
	char				*EA_path;
	char				*WE_path;
	t_rgba				floor_color;
	t_rgba				ceil_color;
	t_map_element		**map_array;
} t_map;

typedef struct s_player
{
	double	viewing_angle;
	double	x;
	double	y;
} t_player;

typedef struct s_global
{
	t_map		*map;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*minimap_img;
} t_global;

typedef struct s_ray
{
	double distance;
	double angle;
}	t_ray;

typedef struct s_point 
{
	int x;
	int y;
}	t_point;

/* Function Definitions */
extern bool	is_wall(t_map_element **map, double x, double y);
extern void cast_all_rays(t_global *data);
extern void	bresenham(mlx_image_t *img, t_point a, t_point b, uint32_t color);
extern void	clear_global(t_global *data);
extern void	minimap(t_global *data);
extern void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize);
extern size_t	strarr_len(char **arr);
extern void	werror(char *msg);
extern int	ft_isnumber(char *str);
extern int ft_isspace2(char c);
extern void	parse_config_file(t_global *data, char *filename);

#endif