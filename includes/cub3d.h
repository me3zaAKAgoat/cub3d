/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:25:57 by me3za             #+#    #+#             */
/*   Updated: 2023/09/22 19:01:02 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "MLX42.h"
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "linked_list.h"

/* Macros */

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define MINIMAP_SIZE 250
# define UNIT_SIZE 4
# define HITBOX_SIZE 1
# define PLAYER_CIRCLE (UNIT_SIZE / 2)
# define OFFSET_X (UNIT_SIZE / 2)
# define OFFSET_Y (UNIT_SIZE / 2)
# define MOVE_SPEED 0.5
# define ROTATION_SPEED .06
# define FOV_DEG 60
# define FOV FOV_DEG * .01745329251
# define PI 3.14159265359
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS WIN_WIDTH / WALL_STRIP_WIDTH

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
}	t_map_element;

typedef struct s_map
{
	char			*no_path;
	char			*so_path;
	char			*ea_path;
	char			*wa_path;
	uint32_t		floor_color;
	uint32_t		ceil_color;
	t_map_element	**map_array;
	size_t			width;
	size_t			height;
}	t_map;

typedef struct s_player
{
	double	viewing_angle;
	double	x;
	double	y;
}	t_player;

typedef struct s_global
{
	t_map		*map;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*game_img;
	mlx_image_t	*hud_img;
}	t_global;

typedef struct s_ray
{
	double	distance;
	double	angle;
	int		id;
	bool	hit_vertical;
}	t_ray;

typedef struct s_point 
{
	int	x;
	int	y;
}	t_point;

/* Function Definitions */

extern	void		print_map(t_map_element **map);
extern	size_t		horizontal_len(t_map_element *arr);
extern	size_t		vertical_len(t_map_element **arr);
extern	void		draw_minimap_background(t_global *data);
extern	void		player_icon(t_global *data, int xm, int ym, int r, uint32_t color);
extern	uint32_t	map_element_color(t_map_element element);
extern	void		move_player(mlx_key_data_t keydata, void *param);
extern	double		normalize_angle(double angle);
extern	bool		is_facing_up(double angle);
extern	bool		is_facing_down(double angle);
extern	bool		is_facing_right(double angle);
extern	bool		is_facing_left(double angle);
extern	void		project_wall(t_global *data, t_ray ray);
extern	bool		is_wall(t_map_element **map, double x, double y);
extern	void		cast_all_rays(t_global *data);
extern	void		bresenham(mlx_image_t *img, t_point a, t_point b, uint32_t color);
extern	void		clear_global(t_global *data);
extern	void		minimap(t_global *data);
extern	void		*ft_realloc(void *ptr, size_t oldsize, size_t newsize);
extern	size_t	strarr_len(char **arr);
extern	void		werror(char *msg);
extern	int		ft_isnumber(char *str);
extern	int		ft_isspace2(char c);
extern	void		parse_config_file(t_global *data, char *filename);

#endif