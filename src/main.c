/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:51 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/23 15:27:42 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MAX_SCREEN_WIDTH 1920
#define MAX_SCREEN_HEIGHT 1080
#define SCALE_FACTOR 40

void	init_data_helper(t_game *game)
{
	game->tex_paths[0] = NULL;
	game->tex_paths[1] = NULL;
	game->tex_paths[2] = NULL;
	game->tex_paths[3] = NULL;
	game->ceiling_color.r = -1;
	game->floor_color.r = -1;
	game->ceiling_color.hex_color = 0;
	game->floor_color.hex_color = 0;
	if (game->map)
	{
		game->map->map_arr = NULL;
		game->map->width = 0;
		game->map->height = 0;
	}
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	game->player.dir = '\0';
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	game->player.ray_dir_x = 0;
	game->player.ray_dir_y = 0;
}

void	init_img_struct(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img_ptr = NULL;
		game->textures[i].addr = NULL;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
		game->textures[i].bits_per_pixel = 0;
		game->textures[i].size_line = 0;
		game->textures[i].endian = 0;
		i++;
	}
}

void	init_data(t_game *game)
{
	init_data_helper(game);
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->scren_width = 0;
	game->scren_height = 0;
	init_img_struct(game);
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left_arrow = 0;
	game->keys.right_arrow = 0;
	game->keys.esc = 0;
	game->move_speed = 0.05;
	game->rot_speed = 0.02;
}

int	init_game(t_game **gamedata, char *file)
{
	*gamedata = ft_malloc(sizeof(t_game));
	(*gamedata)->map = ft_malloc(sizeof(t_map));
	init_data(*gamedata);
	if (!parse(*gamedata, file))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (printf("Error\nUsage: ./cub3D path/<filename>\n"), 1);
	if (SCALE_FACTOR <= 0)
		return (printf("Error\nInvalid scale factor!\n"), 1);
	game = NULL;
	if (!init_game(&game, av[1]))
		return (close_and_free(game), 1);
	camera(game);
	game->scren_height = game->map->height * SCALE_FACTOR;
	game->scren_width = game->map->width * SCALE_FACTOR;
	if (game->scren_height > MAX_SCREEN_HEIGHT)
		game->scren_height = MAX_SCREEN_HEIGHT;
	if (game->scren_width > MAX_SCREEN_WIDTH)
		game->scren_width = MAX_SCREEN_WIDTH;
	if (init_randring(game) == 1)
		return (close_and_free(game), 1);
	return (0);
}
