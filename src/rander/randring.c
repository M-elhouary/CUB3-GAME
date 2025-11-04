/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:23:49 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/04 23:12:05 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int init_randring(t_img *image, t_game *game)
{
     // initilize  connection to the graphical system  
    game->mlx = mlx_init();
    if (!game->mlx)
        return (printf("Error\nmlx_init fail!\n"), 1);
    // creation window
    game->win =  mlx_new_window(game->mlx, game->scren_width, game->scren_height, WIN_TITLE);
    if(!game->win)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (printf("Error\nmlx_new_window fail!\n"), 1);
    }
    // creat image
    game->img = malloc(sizeof(t_img));
    if(!game->img)
        return (printf("Error\nallocation  fail!\n"), 1);
    game->img->img_ptr = mlx_new_image(game->mlx, game->scren_width, game->scren_height);
    if(!game->img->img_ptr)
    {
        mlx_destroy_display(game->mlx);
        mlx_destroy_window(game->mlx, game->win);
        free(game->mlx);
        return (printf("Error\nmlx_new_game->img fail!\n"), 1);
    }
    game->img->img_pex_ptr =  mlx_get_data_addr(game->img->img_ptr, &game->img->bit_per_pixel, 
        &game->img->size_line, &game->img->endian);
    // handle key press 
    draw(game,  game->img);
    mlx_hook(game->win, 2, 1L<<0, handle_key, game);
    mlx_hook(game->win, 17, 0, handle_win_close, NULL);
    move(game);
    mlx_loop(game->mlx);
    return 0;
    
}
