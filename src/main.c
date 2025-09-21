/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:51 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/21 22:07:58 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"





void	init_data(t_game *game)
{
    game->tex_paths[0] = NULL;
    game->tex_paths[1] = NULL;
    game->tex_paths[2] = NULL;
    game->tex_paths[3] = NULL;
    game->ceiling_color = -1;
    game->floor_color = -1;
    game->map->map_arr = NULL;
    game->map->cols = 0;
    game->map->rows = 0;
    game->player.x = 0;
    game->player.y = 0;
}




int	init_game(t_game **gamedata, char *file)
{
	*gamedata = malloc(sizeof(t_game));
	if (!*gamedata)
		return (printf("Error\nmalloc\n"),0);
	(*gamedata)->map = malloc(sizeof(t_map));
    if (!(*gamedata)->map)
    {
        free(*gamedata);
		return (printf("Error\nmalloc\n"),0);
    }
    init_data(*gamedata);
    if (!parse((*gamedata)->map, file))
	{
		free((*gamedata)->map);
		free(*gamedata);
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
    t_game *game;
    if (ac != 2)
		return (printf("Error\nUsage: ./cub3D path/<filename>\n"), 1);
    if (!init_game(&game, av[1]))
        return (1);
    // game->mlx = mlx_init();
    // if (!game->mlx)
    //     return (ft_printf("Error\nmlx_init fail!\n"), 0);
    // game->win = 
    
    //rendring here
    return (0);
}