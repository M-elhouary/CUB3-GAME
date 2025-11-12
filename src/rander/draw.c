/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:09 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/13 00:00:02 by mel-houa         ###   ########.fr       */
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
    double t;
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
            put_pixel(screen_x, y, img, game->ceiling_color.hex_color);  // add the color from the map.cup file
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
            put_pixel(screen_x, y, img, game->floor_color.hex_color);  // add the color from the map.cup file
            screen_x++;
        }
        y++;
    }
}
// ???????
 
unsigned int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
    char    *dst;

    if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height)
        return (0x0); // Return black if coordinates are out of bounds
    dst = texture->addr + (tex_y * texture->size_line + tex_x * (texture->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}


int draw(t_game *game, t_img *img)
{
    // for variables used in drawing
    t_draw_vars vars; 
    t_ray_hit   hit;
    // for texture mapping
    t_texture   *texture;
    // for texture coordinates
    int         tex_x;
    int         tex_y;
    // for texture step and position
    double      tex_step;
    double      tex_pos;
    double       camera_x;
    // drawing ceiling and floors
    draw_ceiling_and_floor(game, img);
    //screen column
    vars.screen_x = 0;
    while (vars.screen_x < game->scren_width)
    {
        // FIX Correct Ray Direction Math 
        // camera_x maps the screen column to the range [-1, 1] for a correct FOV

        // 
        camera_x = 2 * (double)vars.screen_x / (double)game->scren_width - 1;
        vars.ray_x = game->player.dir_x + game->player.plane_x * camera_x;
        vars.ray_y = game->player.dir_y + game->player.plane_y * camera_x;
        
        // Cast the ray using our upgraded function
        hit = cast_ray(game, vars.ray_x, vars.ray_y);

        //  FIX Correct for Fisheye Distortion
        // This math corrects the distance to prevent walls from looking curved.
        double correct_dist = hit.distance * (vars.ray_x * game->player.dir_x + vars.ray_y * game->player.dir_y);

        // Calculate wall height based on the CORRECTED distance
        vars.wall_height = (int)(game->scren_height / correct_dist);

        // Calculate where to start and stop drawing the wall slice
        vars.start_y = (game->scren_height - vars.wall_height) / 2;
        if (vars.start_y < 0)
             vars.start_y = 0;
        vars.end_y = vars.start_y + vars.wall_height;
        if (vars.end_y >= game->scren_height)
            vars.end_y = game->scren_height - 1;
        
        // TEXTURE LOGIC
        // 1. Determine which texture to use based on which side was hit.
        if (hit.side == 1 && vars.ray_y < 0)
             texture = &game->textures[0];
        else if (hit.side == 1 && vars.ray_y > 0)
            texture = &game->textures[1];
        else if (hit.side == 0 && vars.ray_x < 0) 
            texture = &game->textures[2];
        else texture = &game->textures[3];

        // 2. Calculate the x-coordinate on the texture.
        tex_x = (int)(hit.wall_x * (double)texture->width);
        
        // 3. Set up variables for drawing the texture slice vertically.
        tex_step = 1.0 * texture->height / vars.wall_height;
        tex_pos = (vars.start_y - game->scren_height / 2 + vars.wall_height / 2) * tex_step;

        // Draw the vertical line at this screen column
        vars.y = vars.start_y;
        while (vars.y < vars.end_y)
        {
            // 4. Get the y-coordinate on the texture and get the color.
            tex_y = (int)tex_pos;
            tex_pos += tex_step;
            unsigned int color = get_texture_color(texture, tex_x, tex_y);
            put_pixel(vars.screen_x, vars.y, img, color);
            vars.y++;
        }
        vars.screen_x++;
    }
    mini_map(game, game->img);
    mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
    return 0;
}