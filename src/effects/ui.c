/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                              :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2026/01/19 22:50:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/19 22:50:00 by game-dev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void put_px(t_img *img, int x, int y, int color)
{
    int idx;
    if (!img || !img->img_pex_ptr)
        return;
    if (x < 0 || x >= img->size_line / (img->bit_per_pixel / 8) || y < 0 || y >= 1080)
        return;
    idx = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
    *(unsigned int *)(img->img_pex_ptr + idx) = color;
}

void render_damage_direction(t_game *game, t_img *img)
{
    int cx, cy;
    int len;
    int i;
    double ax;
    double ay;

    if (!game || !img)
        return;
    if (game->damage_dir_timer <= 0)
        return;
    cx = game->scren_width / 2;
    cy = game->scren_height / 2;
    len = 30; /* length of indicator line */
    ax = cos((double)game->last_damage_angle);
    ay = sin((double)game->last_damage_angle);
    for (i = 0; i < len; i++)
    {
        int x = cx + (int)(ax * (double)i);
        int y = cy + (int)(ay * (double)i);
        put_px(img, x, y, 0xFF0000);
    }
    game->damage_dir_timer--;
}
