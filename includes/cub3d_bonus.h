/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:25:57 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/04 05:06:52 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "MLX42.h"
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

/* Macros */

# include "macros.h"

/* Types */

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
}	t_map_element;

typedef struct s_map
{
	xpm_t			*no_file;
	xpm_t			*so_file;
	xpm_t			*ea_file;
	xpm_t			*we_file;
	xpm_t			*door_file;
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
	bool		cursor_enabled;
}	t_global;

typedef struct s_double_couple
{
	double	x;
	double	y;
}	t_double_couple;

typedef struct s_ray
{
	double			distance;
	double			angle;
	int				id;
	bool			is_facing_up;
	bool			is_facing_right;
	bool			hit_vertical;
	t_double_couple	wall_hit_vertical;
	t_double_couple	wall_hit_horizontal;
}	t_ray;

typedef enum e_move_direction
{
	forward,
	backward,
	right,
	left
}	t_move_direction;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_wall_data
{
	int	bottom;
	int	top;
	int	strip_height;
}	t_wall_data;

typedef struct s_distance
{
	double	no_fishbowl;
	double	to_projection_plane;
	int		from_top;
}	t_distance;

typedef struct s_sides
{
	int	top;
	int	bottom;
	int	left;
	int	right;
}	t_sides;

/* Function Definitions */

extern	size_t			count_char(char *str, char c);
extern	bool			extraneous_lines(int fd);
extern	bool			color_invalid(char **colors);
extern	void			move_fb(t_global *data, \
						t_double_couple *fs_step, bool forward);
extern	void			move_lr(t_global *data, \
						t_double_couple *lr_step, bool left);
extern	void			square(t_global *data, t_double_couple xy,
							uint32_t color, int edge_size);
extern	void			draw_minimap_unit(t_global *data, \
						t_point *iterators, t_sides *sides);
extern	bool			is_wall(t_map *map, double x, double y);
extern	void			cursor_handler(double x, double y, void *param);
extern	bool			hitbox_compromised(\
						t_global *data, double viewing_angle);
extern	uint32_t		map_element_color(t_map_element element);
extern	void			minimap_bg_init(\
						t_global *data, t_sides *sides, t_point *iterators);
extern	bool			player_sp(t_map_element **map_array, int x, int y);
extern	void			initiate_wall_values(\
						t_wall_data *wall, t_distance *distance);
extern	void			interact_with_door(t_global *data);
extern	void			horizontal_intersection_init_kms(
							t_double_couple *intercept, t_double_couple *step,
							t_double_couple xy, t_ray *ray);
extern	void			vertical_intersection_init_kms(
							t_double_couple *intercept, t_double_couple *step,
							t_double_couple xy, t_ray *ray);
extern	void			horizontal_intersection_init(t_double_couple *intercept,
							t_double_couple *step, t_double_couple xy,
							t_ray *ray);

extern	void			vertical_intersection_init(t_double_couple *intercept,
							t_double_couple *step, t_double_couple xy,
							t_ray *ray);
extern	double		intersection_distance_kms(t_map *map,
							double x, double y, t_ray *ray);
extern	void			cursor_handler(double x, double y, void *param);
extern	void			interact_with_door(t_global *data);
extern	size_t		horizontal_len(t_map_element *arr);
extern	size_t		vertical_len(t_map_element **arr);
extern	void			get_map_dimensions(t_global *data);
extern	bool			is_texture_line(char *line);
extern	t_map_element	char_to_map_element(char c);
extern	bool			contacts_void_above(t_map *map, size_t x, size_t y);
extern	bool			contacts_void_down(t_map *map, size_t x, size_t y);
extern	bool			contacts_void_right(t_map *map, size_t x, size_t y);
extern	bool			contacts_void_left(t_map *map, size_t x, size_t y);
extern	bool			contacts_void(t_map *map, size_t x, size_t y);
extern	void			sanitize_map(t_map *map);
extern	double		horizontal_intersection_distance(t_map *map,
							double x, double y, t_ray *ray);
extern	double		vertical_intersection_distance(t_map *map,
							double x, double y, t_ray *ray);
extern	double		intersection_distance(t_map *map,
							double x, double y, t_ray *ray);
extern	double		dternary(bool statement,
							double fexpression, double sexpression);
extern	int			iternary(bool statement, int fexpression, int sexpression);
extern	double		initial_angle(t_map_element element);
extern	t_map_element	char_to_map_element(char c);
extern	size_t		horizontal_len(t_map_element *arr);
extern	size_t		vertical_len(t_map_element **arr);
extern	void			parse_map(t_global *data, int fd);
extern	void			get_map_dimensions(t_global *data);
extern	void			uniform_arrays_width(t_global *data);
extern	char			*skip_wspace(char *str);
extern	void			render_game(t_global *data);
extern	void			print_map(t_map_element **map);
extern	size_t		horizontal_len(t_map_element *arr);
extern	size_t		vertical_len(t_map_element **arr);
extern	void			draw_minimap_background(t_global *data);
extern	uint32_t		map_element_color(t_map_element element);
extern	void			move_player(void *param);
extern	double		sanitize_angle(double angle);
extern	bool			is_facing_up(double angle);
extern	bool			is_facing_down(double angle);
extern	bool			is_facing_right(double angle);
extern	bool			is_facing_left(double angle);
extern	void			project_ray(t_global *data, t_ray *ray);
extern	bool			is_wall(t_map *map, double x, double y);
extern	void			cast_rays(t_global *data);
extern	void			bresenham(mlx_image_t *img,
							t_point a, t_point b, uint32_t color);
extern	void			clear_global(t_global *data);
extern	void			minimap(t_global *data);
extern	void			*ft_realloc(void *ptr, size_t oldsize, size_t newsize);
extern	size_t		strarr_len(char **arr);
extern	void			werror(char *msg);
extern	int			ft_isnumber(char *str);
extern	int			ft_isspace2(char c);
extern	void			parse_config_file(t_global *data, char *filename);

#endif