/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2026/01/19 21:45:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/19 21:45:00 by game-dev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static float frand(int seed)
{
    /* cheap pseudo-random in [0,1] */
    int n = (seed * 1103515245 + 12345) & 0x7fffffff;
    return (float)(n % 1000) / 1000.0f;
}

void trigger_screen_shake(t_game *game, float amount, float duration)
{
    if (!game)
        return;
    if (amount > game->camera_fx.shake_amount)
        game->camera_fx.shake_amount = amount;
    if (duration > game->camera_fx.shake_duration)
        game->camera_fx.shake_duration = duration;
}

void update_camera_effects(t_game *game)
{
    float shake = 0.0f;
    float bob = 0.0f;
    float tilt = 0.0f;
    int seed;

    if (!game)
        return;
    game->camera_fx.frame++;

    /* decay shake over time */
    if (game->camera_fx.shake_duration > 0.0f)
    {
        game->camera_fx.shake_duration -= 1.0f;
        if (game->camera_fx.shake_duration < 0.0f)
            game->camera_fx.shake_duration = 0.0f;
        shake = game->camera_fx.shake_amount * (game->camera_fx.shake_duration / (game->camera_fx.shake_duration + 10.0f));
    }
    else
    {
        game->camera_fx.shake_amount *= 0.9f;
    }

    /* random offsets for shake */
    seed = game->camera_fx.frame;
    game->camera_fx.shake_offset_x = (int)((frand(seed) - 0.5f) * 2.0f * shake);
    game->camera_fx.shake_offset_y = (int)((frand(seed + 7) - 0.5f) * 2.0f * shake);

    /* simple head bob when moving */
    if (game->keys.w || game->keys.a || game->keys.s || game->keys.d)
    {
        bob = 2.0f + game->camera_fx.bob_amount;
        game->camera_fx.shake_offset_y += (int)(sin((double)game->camera_fx.frame * 0.2) * bob);
    }

    /* strafing tilt -> small horizontal offset */
    if (game->keys.a)
        tilt = -game->camera_fx.tilt_amount;
    else if (game->keys.d)
        tilt = game->camera_fx.tilt_amount;
    game->camera_fx.shake_offset_x += (int)tilt;
}
