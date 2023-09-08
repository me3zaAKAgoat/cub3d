/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:26:38 by me3za             #+#    #+#             */
/*   Updated: 2023/09/08 00:26:39 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t *image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void *param)
{
    for (int32_t i = 0; i < image->width; ++i)
    {
        for (int32_t y = 0; y < image->height; ++y)
        {
            uint32_t color = ft_pixel(
                rand() % 0xFF, // R
                rand() % 0xFF, // G
                rand() % 0xFF, // B
                rand() % 0xFF  // A
            );
            mlx_put_pixel(image, i, y, color);
        }
    }
}

void ft_hook(void *param)
{
    mlx_t *mlx = param;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        image->instances[0].y -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        image->instances[0].y += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        image->instances[0].x -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char *argv[])
{
    mlx_t *mlx;

    // Gotta error check this stuff
    if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (!(image = mlx_new_image(mlx, 128, 128)))
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (mlx_image_to_window(mlx, image, 0, 0) == -1)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }

    mlx_loop_hook(mlx, ft_randomize, mlx);
    mlx_loop_hook(mlx, ft_hook, mlx);

    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}
