/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhilal <selhilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:05:50 by echoukri          #+#    #+#             */
/*   Updated: 2023/09/25 15:09:52 by selhilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_global_defaults(t_global *data, t_map *map)
{
	data->map = map;
	data->map->ea_file = NULL;
	data->map->no_file = NULL;
	data->map->so_file = NULL;
	data->map->we_file = NULL;
	data->map->height = 0;
	data->map->width = 0;
	data->map->ceil_color = 0;
	data->map->floor_color = 0;
	data->map->map_array = NULL;
	data->game_img = NULL;
	data->hud_img = NULL;
	data->mlx = NULL;
}

void	quit(mlx_key_data_t keydata, void *param)
{
	(void)keydata;
	if (mlx_is_key_down((mlx_t *)param, MLX_KEY_ESCAPE))
		mlx_close_window((mlx_t *)param);
}

void	sanitization(int ac, char **av)
{
	if (ac != 2)
		return (werror("Error\nWrong number of arguments was given."), exit(1));
	if (ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 4))
		return (werror("Error\nConfig file must end in '.cub'."), exit(1));
}

int	main(int ac, char **av)
{
	t_map		map;
	t_global	data;

	set_global_defaults(&data, &map);
	sanitization(ac, av);
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
	render_game(&data);
	mlx_loop_hook(data.mlx, move_player, &data);
	mlx_key_hook(data.mlx, quit, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	exit(EXIT_SUCCESS);
}
