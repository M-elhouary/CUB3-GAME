/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:09 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/04 23:33:07 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void put_pixel(int x, int y, t_img *img, int color)
{
    int offset;
    offset = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
    *(unsigned int *)(img->img_pex_ptr + offset) = color;
}

void draw_ceiling_and_floor(t_game *game, t_img *img)
{
    int screen_x;
    int y;

    // Fill ceiling (top half)
    y = 0;
    while (y < game->scren_height / 2)
    {
        screen_x = 0;
        while (screen_x < game->scren_width)
        {
            put_pixel(screen_x, y, img, 0x5fc5e0);  // ceiling color
            screen_x++;
        }
        y++;
    }
    // Fill floor (bottom half)
    while (y < game->scren_height)
    {
        screen_x = 0;
        while (screen_x < game->scren_width)
        {
            put_pixel(screen_x, y, img, 0x665e5c);  // floor color
            screen_x++;
        }
        y++;
    }
}

int draw(t_game *game, t_img *img)
{
    int screen_x;
    int y;
    int start_y;
    int wall_height;
    int end_y;
    double ray_x;
    double ray_y;
    double distance;
    double t;
    // drawing ceiling and floor
    draw_ceiling_and_floor(game, img);
    //Raycasting loop - One ray per screen column
    screen_x = 0;
    while (screen_x < game->scren_width)
    {
        // Calculate t (0.0 to 1.0) for this screen column
        t = (double)screen_x / game->scren_width;
        // Calculate ray direction for this column
        ray_x = game->player.dir_x + (game->player.plan_x * t);
        ray_y = game->player.dir_y + (game->player.plan_y * t);
        // Cast ray and get distance to wall
        distance = cast_ray(game, ray_x, ray_y);
        // Calculate wall height based on distance
        wall_height = (int)(game->scren_height / distance);
        // Clamp wall height to screen
        if (wall_height > game->scren_height)
            wall_height = game->scren_height;
        // Calculate where to start drawing (center vertically)
        start_y = (game->scren_height - wall_height) / 2;
        end_y = start_y + wall_height;
        // Draw vertical line at this screen column
        y = start_y;
        while (y < end_y)
        {
            put_pixel(screen_x, y, img, 0x304f24);  // wall color
            y++;
        }
        screen_x++;
    }
    //Display on screen
    mini_map(game, img);
    mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
    return 0;
}

 