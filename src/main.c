/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:51 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/23 17:04:53 by mel-houa         ###   ########.fr       */
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
  game->map->map_arr = NULL;
  game->map->width = 0;
  game->map->height = 0;
  game->player.x = 0;
  game->player.y = 0;
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
    t_img *image;
    if (ac != 2)
		return (printf("Error\nUsage: ./cub3D path/<filename>\n"), 1);
    if (!init_game(&game, av[1]))
        return (1);
    // initilize  connection to the graphical system  
    game->mlx = mlx_init();
    if (!game->mlx)
        return (printf("Error\nmlx_init fail!\n"), 1);
    // creation window
    game->win =  mlx_new_window(game->mlx, WIN_WIDTH,WIN_HEIGHT, WIN_TITLE);
    if(!game->win)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (printf("Error\nmlx_new_window fail!\n"), 1);
    }
    // creat image
    image = malloc(sizeof(t_img));
    if(!image)
        return (printf("Error\nallocation  fail!\n"), 1);
    image->img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
    if(!image->img_ptr)
    {
        mlx_destroy_display(game->mlx);
        mlx_destroy_window(game->mlx, game->win);
        free(game->mlx);
        return (printf("Error\nmlx_new_image fail!\n"), 1);
    }
    image->img_pex_ptr =  (image->img_ptr, &image->bits_per_pexile, 
        &image->size_line, &image->endian);
    // handle key press 
    mlx_key_hook(game->win, handle_key, NULL); 
    mlx_hook(game->win, 2, 1L << 0, handle_win_close, NULL);
    
    mlx_loop(game->mlx);
    return (0);
}