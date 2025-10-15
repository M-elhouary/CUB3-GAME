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
    image = malloc(sizeof(t_img));
    if(!image)
        return (printf("Error\nallocation  fail!\n"), 1);
    image->img_ptr = mlx_new_image(game->mlx, game->width, game->height);
    if(!image->img_ptr)
    {
        mlx_destroy_display(game->mlx);
        mlx_destroy_window(game->mlx, game->win);
        free(game->mlx);
        return (printf("Error\nmlx_new_image fail!\n"), 1);
    }
    image->img_pex_ptr =  mlx_get_data_addr(image->img_ptr, &image->bit_per_pixel, 
        &image->size_line, &image->endian);
    // handle key press 
    draw(game, image);
    // mlx_key_hook(game->win, handle_key, NULL);  
     mlx_hook(game->win, 17, 0, handle_win_close, NULL);
    mlx_loop(game->mlx);
    return 0;
    
}