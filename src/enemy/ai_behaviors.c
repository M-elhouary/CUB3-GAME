/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_behaviors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2026/01/19 22:15:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/19 22:15:00 by game-dev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Flanking behavior: move 90 degrees to player's side */
void ai_flank(t_object *enemy, t_player *player)
{
    double angle;
    if (!enemy || !player)
        return;
    angle = atan2(player->pos_y - enemy->pos_y, player->pos_x - enemy->pos_x);
    /* offset 90 degrees left or right intelligently */
    if (sin(angle) > 0)
        angle += M_PI / 2.0;
    else
        angle -= M_PI / 2.0;
    enemy->pos_x += cos(angle) * 0.025;
    enemy->pos_y += sin(angle) * 0.025;
}

/* Group tactics: coordinate to surround and overwhelm */
void ai_group_attack(t_object **enemies, int count, t_player *player)
{
    int i;
    int flankers;
    double angle;
    
    if (!enemies || count <= 0 || !player)
        return;
    flankers = 0;
    for (i = 0; i < count; i++)
    {
        if (!enemies[i] || enemies[i]->type != OBJ_ENEMY || enemies[i]->health <= 0)
            continue;
        if (flankers % 2 == 0 && flankers < count / 2)
        {
            ai_flank(enemies[i], player);
            flankers++;
        }
        else
        {
            angle = atan2(player->pos_y - enemies[i]->pos_y,
                         player->pos_x - enemies[i]->pos_x);
            enemies[i]->pos_x += cos(angle) * 0.015;
            enemies[i]->pos_y += sin(angle) * 0.015;
        }
    }
}

/* Use environment: detect and use cover near walls */
void ai_use_environment(t_object *enemy, t_game *game)
{
    double side_x, side_y;
    
    if (!enemy || !game)
        return;
    if (is_wall(game, enemy->pos_x, enemy->pos_y))
    {
        enemy->pos_x -= 0.015;
        enemy->pos_y -= 0.015;
        return;
    }
    /* position near walls for cover */
    side_x = enemy->pos_x + 1.0;
    if (is_wall(game, side_x, enemy->pos_y))
        enemy->pos_x -= 0.01;
    side_x = enemy->pos_x - 1.0;
    if (is_wall(game, side_x, enemy->pos_y))
        enemy->pos_x += 0.01;
    side_y = enemy->pos_y + 1.0;
    if (is_wall(game, enemy->pos_x, side_y))
        enemy->pos_y -= 0.01;
    side_y = enemy->pos_y - 1.0;
    if (is_wall(game, enemy->pos_x, side_y))
        enemy->pos_y += 0.01;
}
