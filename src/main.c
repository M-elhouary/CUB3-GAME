/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:51 by moirhira          #+#    #+#             */
/*   Updated: 2025/11/19 22:58:48 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_game *game)
{
	game->tex_paths[0] = NULL;
	game->tex_paths[1] = NULL;
	game->tex_paths[2] = NULL;
	game->tex_paths[3] = NULL;
	game->ceiling_color.r = -1;
	game->floor_color.r = -1;
	game->ceiling_color.hex_color = 0;
	game->floor_color.hex_color = 0;
	game->map->map_arr = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
}

int	init_game(t_game **gamedata, char *file)
{
	*gamedata = malloc(sizeof(t_game));
	if (!*gamedata)
		return (printf("Error\nmalloc\n"), 0);
	(*gamedata)->map = malloc(sizeof(t_map));
	if (!(*gamedata)->map)
		return (printf("Error\nmalloc\n"), 0);
	init_data(*gamedata);
	if (!parse(*gamedata, file))
		return (0);
	return (1);
}

void	win_scal(t_game *game)
{
	game->scren_height = game->map->height * 40;
	game->scren_width = game->map->width * 40;
}

int	main(int ac, char **av)
{
	t_game *game;
	t_img *image;
	if (ac != 2)
		return (printf("Error\nUsage: ./cub3D path/<filename>\n"), 1);
	if (!init_game(&game, av[1]))
		return (1);
	camera(game);
	win_scal(game);
	if (init_randring(game) == 1)
		return (1);
	return (0);
}