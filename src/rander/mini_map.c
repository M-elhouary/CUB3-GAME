/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:59:34 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/06 00:05:43 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_ceiling(t_img *img, t_game *game, int x, int y)
{
    int dx;
    int dy = 0;
    int offset_x = game->scren_width - (game->map->width * 5) - 5;  // right side
    int offset_y = game->scren_height - (game->map->height * 5) - 5; // bottom
    
    while (dy < 5)
    {
        dx = 0;
        while (dx < 5)
        {
                put_pixel(offset_x + x * 5 + dx, offset_y + y * 5 + dy, img, 0xfb2b);
                dx++;
        }
        dy++;
    }
}


void draw_floor(t_img *img, t_game *game, int x, int y)
{
    int dx;
    int dy = 0;
    int offset_x = game->scren_width - (game->map->width * 5) - 5;  // right side
    int offset_y = game->scren_height - (game->map->height * 5) - 5; // bottom
    
    while (dy < 5)
    {
        dx = 0;
        while (dx < 5)
        {
                put_pixel(offset_x + x * 5 + dx, offset_y + y * 5 + dy, img, 0xfbf82b);
                dx++;
        }
        dy++;
    }
}

void draw_wall(t_img *img, t_game *game, int x, int y)
{
    int dx;
    int dy;
    int offset_x = game->scren_width - (game->map->width * 5) - 5;  // right side
    int offset_y = game->scren_height - (game->map->height * 5) - 5; // bottom
    
    dy = 0;
    while (dy < 5)
    {
        dx = 0;
        while (dx < 5)
        {
            put_pixel(offset_x + (x * 5 + dx), offset_y + y * 5 + dy, img, 0x2b41fb);
            dx++;
        }
        dy++;
    }
}


void draw_player(t_img *img, t_game *game, double x, double y)
{
    int dx;
    int dy;
    int offset_x = game->scren_width - (game->map->width * 3) - 3;  // right side
    int offset_y = game->scren_height - (game->map->height * 3) - 3; // bottom
    
    dy = -2;
    while (dy < 3)
    {
        dx = -2;
        while (dx < 2)
        {
            put_pixel(offset_x + (int)(x * 3 )+ (dx), offset_y + (int)(y * 3)+ (dy), img, 0x27F5F2);
            dx++;
        }
        dy++;
    }
}


// void draw_player_dir(t_img *img, t_game *game, double x, double y)
// {

//     double step;
//     double length;
//     int steps ;
//     int i;
//     int offset_x = game->scren_width - (game->map->width * 3) - 3;  // right side
//     int offset_y = game->scren_height - (game->map->height * 3) - 3; // bottom
    
//     i = 0;
//     length = 0.90;    // length in tiles for the direction line
//     step = 0.01;     // step in tiles
//     steps = (int)(length / step);
//     while(i < steps)
//     {
//         put_pixel(offset_x + (int)(x * 3), offset_y + (int)(y * 3), img, 0xFF0000);
//         x += (double)game->player.dir_x * step;
//         y += (double)game->player.dir_y * step;
//         i++;
//     }
// }

int check_player(char player)
{
    return(player == 'W' || player == 'N' || player == 'E' || player == 'S');
}




int mini_map(t_game *game, t_img *img)
{
        
    int y, x;
    y = 0;
    x = 0;
    
    while (y <  game->scren_height)
    {
        x = 0;
        while (x < game->scren_width)
        {
                if(y < game->map->height && x < game->map->width && game->map->map_arr[y][x] == '1')
                    draw_wall(img, game, x, y);
                else if(y < game->map->height && x < game->map->width && ( game->map->map_arr[y][x] == '0' || check_player(game->map->map_arr[y][x])))
                     draw_floor(img, game, x, y);
                else if (y < game->map->height && x < game->map->width && game->map->map_arr[y][x] == ' ')
                         draw_ceiling(img, game, x, y);
            x++;
        }
        y++;
    }
    draw_player(img, game, game->player.x, game->player.y);
    draw_player_dir(img, game, game->player.x, game->player.y);
    mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
    return 0;
}
