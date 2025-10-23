/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:23:49 by mel-houa          #+#    #+#             */
/*   Updated: 2025/10/23 22:48:31 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int key_press_handler(int keycode, t_game *data)
{
    if (keycode == 119) // w
        data->keys.w = 1;
    if (keycode == 97) // a
        data->keys.s = 1;
    if (keycode == 100) // d
        data->keys.d = 1;
    if (keycode == 115) // s
        data->keys.s = 1;
    if (keycode == 65363) // ->
        data->keys.right_arrow = 1;
    if (keycode == 65361) // <-
        data->keys.left_arrow = 1;
    if (keycode == 65307) // esc
    {
        printf("esc presed \n");
        data->keys.esc = 1;
    }
    return (0);
}


int key_release_handler(int keycode, t_game *data)
{
    if (keycode == 119) // w
        data->keys.w = 0;
    if (keycode == 97) // a
        data->keys.s = 0;
    if (keycode == 100) // d
        data->keys.d = 0;
    if (keycode == 115) // s
        data->keys.s = 0;
    if (keycode == 65363) // ->
        data->keys.right_arrow = 0;
    if (keycode == 65361) // <-
        data->keys.left_arrow = 0;
    return (0);
}



int game_loop(t_game *game)
{
    if (game->keys.esc)
        close_and_free(game);
        
    printf("Pos: (%.2f, %.2f) | Dir: (%.2f, %.2f)\n", 
            game->player.plane_x, game->player.plane_y, game->player.dir_x, game->player.dir_y);
    return (0);
}


int ft_init_randring(t_img *image, t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (printf("Error\nmlx_init failed!\n"), 1);
    game->win =  mlx_new_window(game->mlx, game->win_width, game->win_height, WIN_TITLE);
    if(!game->win)
    {
        free(game->mlx);
        return (printf("Error\nmlx_new_window fail!\n"), 1);
    }
    mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
    mlx_hook(game->win, 17, 0, close_and_free, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
    return 0;
    
}













// game->img = malloc(sizeof(t_img));
// if(!game->img)
// {
//     close_and_free(game);
//     return (printf("Error\nallocation  fail!\n"), 1);
// }
// game->img->img_ptr = mlx_new_image(game->mlx, game->win_width, game->win_height);
// if(!game->img->img_ptr)
// {
//     close_and_free(game);
//     return (printf("Error\nmlx_new_image failed!\n"), 1);
// }
// game->img->img_pex_ptr =  mlx_get_data_addr(game->img->img_ptr, &game->img->bit_per_pixel, 
//     &game->img->size_line, &game->img->endian);
// move(game);
 // draw(game,  game->img);