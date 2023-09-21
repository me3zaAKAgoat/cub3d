/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:05:50 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/21 22:34:05 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_global_defaults(t_global *data, t_map *map)
{
	data->map = map;
	data->map->EA_path = NULL;
	data->map->NO_path = NULL;
	data->map->SO_path = NULL;
	data->map->WE_path = NULL;
	data->map->ceil_color = 0;
	data->map->floor_color = 0;
	data->map->map_array = NULL;
	data->game_img = NULL;
	data->hud_img = NULL;
	data->mlx = NULL;
}

void	quit(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

int	main(int ac, char **av)
{
	t_map		map;
	t_global	data;

	(void)ac;
	set_global_defaults(&data, &map);
	parse_config_file(&data, av[1]);
	data.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", false);
	if (!data.mlx)
		werror("mlx init failed.");
	data.game_img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.hud_img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.game_img || !data.hud_img)
		werror("mlx new img failed.");
	if (mlx_image_to_window(data.mlx, data.game_img, 0, 0) < 0 || mlx_image_to_window(data.mlx, data.hud_img, 0, 0) < 0)
		werror("mlx new img to window failed.");
	minimap(&data);
	mlx_key_hook(data.mlx, move_player, &data);
	mlx_loop_hook(data.mlx, quit, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	exit(EXIT_SUCCESS);
}