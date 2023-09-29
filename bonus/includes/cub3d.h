/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:25:57 by me3za             #+#    #+#             */
/*   Updated: 2023/09/29 18:38:59 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include "linked_list.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define MINIMAP_SIZE 160
# define UNIT_SIZE 10
# define TEXTURE_SIZE 64
# define HITBOX_SIZE 0.6
# define MINIMAP_OFFSET_X 5
# define MINIMAP_OFFSET_Y 5
# define MOVE_SPEED 0.2
# define ROTATION_SPEED 0.01
# define FOV 0.6981317004 // 40 * 0.01745329251
# define WALL_STRIP_WIDTH 1
# define DDTPP 2291.83118183 //(WIN_WIDTH / 2) / tan(FOV / 2)
# define NUM_RAYS 1600       //(WIN_WIDTH / WALL_STRIP_WIDTH)
# define PLUS 1
# define MINUS 0

typedef enum e_map_element
{
	SURFACE_PLAYABLE,
	SURFACE_NOT_PLAYABLE,
	DOOR_OPEN,
	DOOR_CLOSED,
	WALL,
	NORTH,
	EAST,
	WEST,
	SOUTH,
	HORIZONTAL_TERM
}						t_map_element;

typedef struct s_squre
{
	int	left;
	int	top;
	int	right;
	int	bottom;
}			t_squre;

typedef struct s_map
{
	xpm_t				*no_file;
	xpm_t				*so_file;
	xpm_t				*ea_file;
	xpm_t				*we_file;
	xpm_t				*door_file;
	uint32_t			floor_color;
	uint32_t			ceil_color;
	t_map_element		**map_array;
	size_t				width;
	size_t				height;
}						t_map;

typedef struct s_player
{
	double				view_angle;
	double				x;
	double				y;
}						t_player;

typedef struct s_steps
{
	double		fs_xstep;
	double		fs_ystep;
	double		lr_xstep;
	double		lr_yste;
}						t_steps;

typedef struct s_global
{
	t_map				*map;
	t_player			player;
	mlx_t				*mlx;
	int					left;
	int					right;
	int					top;
	int					bottom;
	mlx_image_t			*game_img;
	mlx_image_t			*hud_img;
	bool				cursor_enabled;
	t_squre				squre;
	t_steps				steps;
}						t_global;

typedef struct s_double_couple
{
	double				x;
	double				y;
}						t_double_couple;

typedef struct s_ray
{
	double				distance;
	double				angle;
	int					id;
	bool				is_facing_up;
	bool				is_facing_right;
	bool				hit_v;
	t_double_couple		hit_ver;
	t_double_couple		hit_hor;
}						t_ray;

typedef enum e_move_direction
{
	forward,
	backward,
	right,
	left
}						t_move_direction;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_wall_data
{
	int					bottom;
	int					top;
	int					strip_height;
}						t_wall_data;

typedef struct s_distance
{
	double				no_fishbowl;
	double				pp;
	int					from_top;
}						t_distance;

extern void				key_move_left_right(t_global *data, int flag);
extern void				key_move_up_down(t_global *data, int flag);
extern bool				hitbox_compromised(t_global *data, double view_angle);
extern void				move_player_ut(t_global *data);
extern	double			handle_fishbowl_effect(t_global *data, t_ray *ray,
							t_distance *distance);
extern bool				is_wall_kms(t_map *map, double x, double y);
extern double			intersection_distance_kms(t_map *map, double x,
							double y, t_ray *ray);
extern void				cursor_handler(double x, double y, void *param);
extern void				interact_with_door(t_global *data);
extern size_t			horizontal_len(t_map_element *arr);
extern size_t			vertical_len(t_map_element **arr);
extern void				get_map_dimensions(t_global *data);
extern bool				is_texture_line(char *line);
extern t_map_element	char_to_map_element(char c);
extern bool				contacts_void_above(t_map *map, size_t x, size_t y);
extern bool				contacts_void_down(t_map *map, size_t x, size_t y);
extern bool				contacts_void_right(t_map *map, size_t x, size_t y);
extern bool				contacts_void_left(t_map *map, size_t x, size_t y);
extern bool				contacts_void(t_map *map, size_t x, size_t y);
extern void				sanitize_map(t_map *map);
extern double			horizontal_intersection_distance(t_map *map, double x,
							double y, t_ray *ray);
extern double			vertical_intersection_distance(t_map *map, double x,
							double y, t_ray *ray);
extern double			intersection_distance(t_map *map, double x, double y,
							t_ray *ray);
extern double			dternary(bool statement, double fexpression,
							double sexpression);
extern int				iternary(bool statement, int fexpression,
							int sexpression);
extern double			initial_angle(t_map_element element);
extern t_map_element	char_to_map_element(char c);
extern size_t			horizontal_len(t_map_element *arr);
extern size_t			vertical_len(t_map_element **arr);
extern void				parse_map(t_global *data, int fd);
extern void				get_map_dimensions(t_global *data);
extern void				uniform_arrays_width(t_global *data);
extern char				*skip_wspace(char *str);
extern void				render_game(t_global *data);
extern void				print_map(t_map_element **map);
extern size_t			horizontal_len(t_map_element *arr);
extern size_t			vertical_len(t_map_element **arr);
extern void				draw_minimap_background(t_global *data, int x, int y);
extern void				player_icon(t_global *data, int xm, int ym, int r);
extern uint32_t			map_element_color(t_map_element element);
extern void				move_player(void *param);
extern double			sanitize_angle(double angle);
extern bool				is_facing_up(double angle);
extern bool				is_facing_down(double angle);
extern bool				is_facing_right(double angle);
extern bool				is_facing_left(double angle);
extern void				project_ray(t_global *data, t_ray *ray, xpm_t *xpm);
extern bool				is_wall(t_map *map, double x, double y);
extern void				cast_rays(t_global *data);
extern void				init_vertical_inter(t_double_couple *step, t_ray *ray,
							double *tan_ra);
extern void				init_horizontal_inter(t_double_couple *step, t_ray *ray,
							double *tan_ra);
extern void				bresenham(mlx_image_t *img, t_point a, t_point b,
							uint32_t color);
extern void				clear_global(t_global *data);
extern void				minimap(t_global *data);
extern void				*ft_realloc(void *ptr, size_t oldsize, size_t newsize);
extern size_t			strarr_len(char **arr);
extern void				werror(char *msg);
extern int				ft_isnumber(char *str);
extern int				ft_isspace2(char c);
extern void				parse_config_file(t_global *data, char *filename);
#endif