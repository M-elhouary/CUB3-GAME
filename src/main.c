/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:51 by moirhira          #+#    #+#             */
/*   Updated: 2025/10/23 22:34:20 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_data(t_game *game)
{
  game->tex_paths[0] = NULL;
  game->tex_paths[1] = NULL;
  game->tex_paths[2] = NULL;
  game->tex_paths[3] = NULL;
  game->ceiling_color.r = -1;
  game->floor_color.r = -1;
  game->map->map_arr = NULL;
  game->map->width = 0;
  game->map->height = 0;
  game->player.x = 0;
  game->player.y = 0;
  game->move_speed = 0.05;
  game->move_speed = 0.03;
  game->keys.w = 0;
  game->keys.d = 0;
  game->keys.a = 0;
  game->keys.s = 0;
  game->keys.esc = 0;
  game->keys.left_arrow = 0;
  game->keys.right_arrow = 0;
}

int init_game(t_game **gamedata, char *file)
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

int main(int ac, char **av)
{
  t_game *game;
  if (ac != 2)
    return (printf("Error\nUsage: ./cub3D path/<filename>\n"), 1);
  if (!init_game(&game, av[1]))
    return (close_and_free(game), 1);
  game->win_width = game->map->width * 40;
  game->win_height = game->map->height * 40;
  if (ft_init_randring(game->img, game) == 1)
    return (1);
  close_and_free(game);
  return (0);
}

