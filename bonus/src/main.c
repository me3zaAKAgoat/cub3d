/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:05:50 by echoukri          #+#    #+#             */
/*   Updated: 2023/10/01 14:28:36 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_global_defaults(t_global *data, t_map *map)
{
	data->map = map;
	data->map->ea_file = NULL;
	data->map->no_file = NULL;
	data->map->so_file = NULL;
	data->map->we_file = NULL;
	data->map->door_file = NULL;
	data->map->height = 0;
	data->map->width = 0;
	data->map->ceil_color = 0;
	data->map->floor_color = 0;
	data->map->map_array = NULL;
	data->game_img = NULL;
	data->hud_img = NULL;
	data->mlx = NULL;
	data->cursor_enabled = false;
}

void	simple_key_handlers(mlx_key_data_t keydata, void *param)
{
	t_global	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
		interact_with_door(data);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
	{
		data->cursor_enabled = !data->cursor_enabled;
		mlx_set_cursor_mode(data->mlx,
			iternary(data->cursor_enabled, MLX_MOUSE_NORMAL, MLX_MOUSE_HIDDEN));
	}
}

void	sanitization(int ac, char **av)
{
	if (ac != 2)
		return (werror("Error\nWrong number of arguments was given."), exit(1));
	if (ft_strlen(av[1]) < 4 || \
			ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 4))
		return (werror("Error\nConfig file must end in '.cub'."), exit(1));
}

void	init_img(t_global *data)
{
	data->game_img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->hud_img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->game_img || !data->hud_img)
		werror("mlx new img failed.");
	data->img = mlx_load_png("assets/valorant.png");
	if (!data->img)
	{
		werror("mlx load png failed.");
		exit(EXIT_FAILURE);
	}
	data->first = mlx_texture_to_image(data->mlx, data->img);
	if (!data->first)
	{
		werror("mlx texture to image failed.");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	t_map		map;
	t_global	data;

	set_global_defaults(&data, &map);
	sanitization(ac, av);
	parse_config_file(&data, av[1]);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", true);
	if (!data.mlx)
		werror("mlx init failed.");
	init_img(&data);
	init_sprite(&data);
	if (mlx_image_to_window(data.mlx, data.game_img, 0, 0) < 0
		|| mlx_image_to_window(data.mlx, data.hud_img, 0, 0) < 0 || \
			mlx_image_to_window(data.mlx, data.first, 0, 0) < 0)
		werror("mlx new img to window failed.");
	mlx_set_cursor_mode(data.mlx,
		iternary(data.cursor_enabled, MLX_MOUSE_NORMAL, MLX_MOUSE_HIDDEN));
	render_game(&data);
	mlx_cursor_hook(data.mlx, cursor_handler, &data);
	mlx_key_hook(data.mlx, simple_key_handlers, &data);
	mlx_loop_hook(data.mlx, move_player, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	exit(EXIT_SUCCESS);
}
