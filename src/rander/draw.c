/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:09 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/06 21:23:53 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


typedef struct s_draw
{
    int screen_x;
    int wall_height;
    int start_y;
    int end_y;
    int y;
    double ray_x;
    double ray_y;
    double distance;
    double t; // interpolation factor
}   t_draw_vars;



void put_pixel(int x, int y, t_img *img, int color)
{
    int offset;
    offset = (y * img->size_line) + (x * (img->bit_per_pixel / 8)); // ??
    *(unsigned int *)(img->img_pex_ptr + offset) = color;
}

void draw_ceiling_and_floor(t_game *game, t_img *img)
{
    int screen_x;
    int y;

    // Fill ceiling (top half)
    y = 0;
    while (y < game->scren_height / 2) // ??
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
    t_draw_vars vars; 
    // drawing ceiling and floor
    draw_ceiling_and_floor(game, img);
    //Raycasting loop - One ray per screen column
    vars.screen_x = 0;
    while (vars.screen_x < game->scren_width)
    {
        // Calculate t (0.0 to 1.0) for this screen column
        vars.t = (double)vars.screen_x / game->scren_width;
        // Calculate ray direction for this column
        vars.ray_x = game->player.dir_x + (game->player.plane_x * vars.t);
        vars.ray_y = game->player.dir_y + (game->player.plane_y * vars.t);
        // Cast ray and get distance to wall
        vars.distance = cast_ray(game, vars.ray_x, vars.ray_y);
        // Calculate wall height based on distance
        vars.wall_height = (int)(game->scren_height / vars.distance);
        // Clamp wall height to screen
        if (vars.wall_height > game->scren_height)
            vars.wall_height = game->scren_height;
        // Calculate where to start drawing (center vertically)
        vars.start_y = (game->scren_height - vars.wall_height) / 2;
        vars.end_y = vars.start_y + vars.wall_height;
        // Draw vertical line at this screen column
        vars.y = vars.start_y;
        while (vars.y < vars.end_y)
        {
            put_pixel(vars.screen_x, vars.y, img, 0xeee6e3);  // wall color
            vars.y++;
        }
        vars.screen_x++;
    }
    //Display on screen
    mini_map(game, img);
   // first_draw_player(img, game, game->player.x, game->player.y);
    mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
    return 0;
}

 