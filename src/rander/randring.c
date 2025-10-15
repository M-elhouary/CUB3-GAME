/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:23:49 by mel-houa          #+#    #+#             */
/*   Updated: 2025/09/23 15:38:22 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


// int handle_key(int key, void *param)
// {
//     (void)param;
//     if (key == ESC_KEY)
//         exit(0);
//     return (0);
// }

int handle_win_close(void *param)
{
    (void)param;
    //free
    exit(0);
}



int ft_init_randring(t_img *image, t_game *game)
{
     // initilize  connection to the graphical system  

    game->mlx = mlx_init();
    if (!game->mlx)
        return (printf("Error\nmlx_init fail!\n"), 1);
    // creation window
    game->win =  mlx_new_window(game->mlx, game->width, game->height, WIN_TITLE);
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
    game->img->img_ptr = mlx_new_image(game->mlx, game->width, game->height);
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
    // mlx_key_hook(game->win, handle_key, NULL);
     mlx_hook(game->win, 17, 0, handle_win_close, NULL);
     move(game);
    mlx_loop(game->mlx);
    return 0;
    
}