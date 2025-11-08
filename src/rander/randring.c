/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:23:49 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/06 22:31:08 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int init_randring(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error\nmlx_init failed!\n"), 1);

	if (!load_all_textures(game))
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (printf("Error: Texture loading failed!\n"), 1);
	}
	game->win = mlx_new_window(game->mlx, game->scren_width, game->scren_height, WIN_TITLE);
	if (!game->win)
	{
		free(game->mlx);
		return (printf("Error\nmlx_new_window fail!\n"), 1);
	}
	game->img = malloc(sizeof(t_img));
	if (!game->img)
		return (printf("Error\nallocation  fail!\n"), 1);
	game->img->img_ptr = mlx_new_image(game->mlx, game->scren_width, game->scren_height);
	if (!game->img->img_ptr)
	{
		mlx_destroy_display(game->mlx);
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
		return (printf("Error\nmlx_new_game->img fail!\n"), 1);
	}
	game->img->img_pex_ptr = mlx_get_data_addr(game->img->img_ptr, &game->img->bit_per_pixel,
						   &game->img->size_line, &game->img->endian);

	init_keys(game);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, 17, 0, close_and_free, game);
	mlx_loop_hook(game->mlx, game_update, game);

	mlx_loop(game->mlx);
	return 0;
}