/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impact.c                                          :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2026/01/19 21:50:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/19 21:50:00 by game-dev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void put_pixel_safe(t_img *img, int x, int y, int color)
{
    int idx;
    if (!img || !img->img_pex_ptr)
        return;
    if (x < 0 || x >= img->bit_per_pixel || y < 0 || y >= img->bit_per_pixel)
        return;
    idx = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
    if (idx < 0 || idx >= img->size_line * img->bit_per_pixel)
        return;
    *(unsigned int *)(img->img_pex_ptr + idx) = color;
}

static void draw_circle(t_img *img, int cx, int cy, int r, int color)
{
    int x, y;
    for (y = -r; y <= r; y++)
        for (x = -r; x <= r; x++)
            if (x*x + y*y <= r*r)
                put_pixel_safe(img, cx + x, cy + y, color);
}

static void calculate_screen_pos(t_game *game, double wx, double wy,
                                 int *sx, int *sy, int *size)
{
    double rel_x = wx - game->player.pos_x;
    double rel_y = wy - game->player.pos_y;
    double dist = sqrt(rel_x * rel_x + rel_y * rel_y);
    double angle = atan2(rel_y, rel_x) - atan2(game->player.dir_y, game->player.dir_x);
    while (angle > M_PI) angle -= 2*M_PI;
    while (angle < -M_PI) angle += 2*M_PI;
    *size = (int)((game->scren_height / (dist < 0.1 ? 0.1 : dist)) * 0.15);
    *sx = (int)(game->scren_width / 2 + (angle / (M_PI / 3.0)) * (game->scren_width / 2.0));
    *sy = game->scren_height / 2;
}

void add_impact(t_game *game, double x, double y, int type)
{
    t_impact *imp;

    if (!game)
        return;
    imp = (t_impact *)ft_malloc(sizeof(t_impact));
    if (!imp)
        return;
    imp->x = x;
    imp->y = y;
    imp->type = type;
    imp->lifetime = 24; /* ~0.4s at 60fps */
    imp->texture_frame = 0;
    imp->next = game->impacts;
    game->impacts = imp;

    /* immediate feedback */
    game->hit_marker_timer = 8; /* snappy hit marker */
    trigger_screen_shake(game, 6.0f, 8.0f);
}

void update_impacts(t_game *game)
{
    t_impact *cur, *prev, *next;

    if (!game)
        return;
    prev = NULL;
    cur = game->impacts;
    while (cur)
    {
        cur->lifetime--;
        cur->texture_frame++;
        next = cur->next;
        if (cur->lifetime <= 0)
        {
            if (prev)
                prev->next = next;
            else
                game->impacts = next;
            free(cur);
            cur = next;
            continue;
        }
        prev = cur;
        cur = next;
    }
}

static void draw_damage_number(t_img *img, int x, int y, int value, int color)
{
    /* simple blocky digits 3x5 per digit */
    static const int digits[10][15] = {
        {1,1,1, 1,0,1, 1,0,1, 1,0,1, 1,1,1}, /*0*/
        {0,1,0, 1,1,0, 0,1,0, 0,1,0, 1,1,1}, /*1*/
        {1,1,1, 0,0,1, 1,1,1, 1,0,0, 1,1,1}, /*2*/
        {1,1,1, 0,0,1, 0,1,1, 0,0,1, 1,1,1}, /*3*/
        {1,0,1, 1,0,1, 1,1,1, 0,0,1, 0,0,1}, /*4*/
        {1,1,1, 1,0,0, 1,1,1, 0,0,1, 1,1,1}, /*5*/
        {1,1,1, 1,0,0, 1,1,1, 1,0,1, 1,1,1}, /*6*/
        {1,1,1, 0,0,1, 0,1,0, 0,1,0, 0,1,0}, /*7*/
        {1,1,1, 1,0,1, 1,1,1, 1,0,1, 1,1,1}, /*8*/
        {1,1,1, 1,0,1, 1,1,1, 0,0,1, 1,1,1}  /*9*/
    };
    char buf[12];
    int i, j, k, dx = 0;

    snprintf(buf, sizeof(buf), "%d", value);
    for (k = 0; buf[k]; k++)
    {
        int d = buf[k] - '0';
        for (i = 0; i < 5; i++)
            for (j = 0; j < 3; j++)
                if (digits[d][i*3 + j])
                    put_pixel_safe(img, x + dx + j, y + i, color);
        dx += 4; /* spacing */
    }
}

void add_damage_indicator(t_game *game, double x, double y, int value)
{
    t_damage_indicator *di;
    if (!game)
        return;
    di = (t_damage_indicator *)ft_malloc(sizeof(t_damage_indicator));
    if (!di)
        return;
    di->x = x;
    di->y = y;
    di->value = value;
    di->lifetime = 25;
    di->vy = -0.02; /* float up */
    di->next = game->damage_indicators;
    game->damage_indicators = di;
}

void update_damage_indicators(t_game *game)
{
    t_damage_indicator *cur, *prev, *next;
    if (!game)
        return;
    prev = NULL;
    cur = game->damage_indicators;
    while (cur)
    {
        cur->y += cur->vy;
        cur->lifetime--;
        next = cur->next;
        if (cur->lifetime <= 0)
        {
            if (prev)
                prev->next = next;
            else
                game->damage_indicators = next;
            free(cur);
            cur = next;
            continue;
        }
        prev = cur;
        cur = next;
    }
}

void render_impacts(t_game *game, t_img *img)
{
    t_impact *cur;
    int sx, sy, size;
    int color;

    if (!game || !img)
        return;
    cur = game->impacts;
    while (cur)
    {
        calculate_screen_pos(game, cur->x, cur->y, &sx, &sy, &size);
        if (cur->type == 0) /* blood */
            color = 0xAA0000;
        else if (cur->type == 1) /* bullet hole */
            color = 0x222222;
        else /* explosion */
            color = 0xFF8800;
        draw_circle(img, sx, sy, size > 6 ? 6 : size, color);
        cur = cur->next;
    }
}

void render_damage_indicators(t_game *game, t_img *img)
{
    t_damage_indicator *cur;
    int sx, sy, size;

    if (!game || !img)
        return;
    cur = game->damage_indicators;
    while (cur)
    {
        calculate_screen_pos(game, cur->x, cur->y, &sx, &sy, &size);
        draw_damage_number(img, sx, sy - 10, cur->value, 0xFFFFFF);
        cur = cur->next;
    }
}

void render_hit_marker(t_game *game, t_img *img)
{
    int cx, cy, i;
    if (!game || !img)
        return;
    if (game->hit_marker_timer <= 0)
        return;
    cx = game->scren_width / 2;
    cy = game->scren_height / 2;
    for (i = -8; i <= 8; i++)
    {
        put_pixel_safe(img, cx + i, cy + i, 0xFF0000);
        put_pixel_safe(img, cx + i, cy - i, 0xFF0000);
    }
    game->hit_marker_timer--;
}
