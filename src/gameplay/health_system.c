/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/20 00:24:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Initialize player health system
*/
void	init_health_system(t_health *health)
{
	if (!health)
		return ;
	health->current_hp = 100;
	health->max_hp = 100;
	health->is_alive = 1;
	health->invulnerable_time = 0;
	health->damage_cooldown = 0;
}

/*
** Damage player and record direction from source (world coords)
*/
void	damage_player_from(t_game *game, double src_x, double src_y, int damage_amount)
{
	double angle;
	if (!game)
		return;
	damage_player(&game->health, damage_amount);
	game->stats.total_damage_taken += damage_amount;
	/* record indicator if damage applied */
	if (is_player_invulnerable(&game->health))
	{
		angle = atan2(src_y - game->player.pos_y, src_x - game->player.pos_x);
		game->last_damage_angle = (float)angle;
		game->damage_dir_timer = 20;
		trigger_screen_shake(game, 6.0f, 8.0f);
	}
}

/*
** Deal damage to player with invulnerability frames
*/
void	damage_player(t_health *health, int damage_amount)
{
	if (!health || !health->is_alive || health->invulnerable_time > 0)
		return ;
	health->current_hp -= damage_amount;
	health->invulnerable_time = 30;
	if (health->current_hp <= 0)
	{
		health->current_hp = 0;
		health->is_alive = 0;
	}
}

/*
** Heal player (cannot exceed max hp)
*/
void	heal_player(t_health *health, int heal_amount)
{
	if (!health)
		return ;
	health->current_hp += heal_amount;
	if (health->current_hp > health->max_hp)
		health->current_hp = health->max_hp;
}

/*
** Get current health as percentage (0-100)
*/
int	get_health_percentage(t_health *health)
{
	if (!health || health->max_hp <= 0)
		return (0);
	return ((health->current_hp * 100) / health->max_hp);
}

/*
** Check if player is alive
*/
int	is_player_alive(t_health *health)
{
	if (!health)
		return (0);
	return (health->is_alive && health->current_hp > 0);
}

/*
** Apply invulnerability frames each game tick
*/
void	update_health(t_health *health)
{
	if (!health)
		return ;
	if (health->invulnerable_time > 0)
		health->invulnerable_time--;
	if (health->damage_cooldown > 0)
		health->damage_cooldown--;
}

/*
** Resurrect player with full health
*/
void	respawn_player(t_health *health)
{
	if (!health)
		return ;
	health->current_hp = health->max_hp;
	health->is_alive = 1;
	health->invulnerable_time = 60;
}

/*
** Deal damage to enemy
*/
void	damage_enemy_health(t_object *enemy, int damage)
{
	if (!enemy || enemy->type != OBJ_ENEMY)
		return ;
	enemy->health -= damage;
	if (enemy->health < 0)
		enemy->health = 0;
}

/*
** Heal enemy (for pickups/power-ups)
*/
void	heal_enemy(t_object *enemy, int heal_amount)
{
	if (!enemy || enemy->type != OBJ_ENEMY)
		return ;
	enemy->health += heal_amount;
	if (enemy->health > 100)
		enemy->health = 100;
}

/*
** Check if player was just hit (invulnerability active)
*/
int	is_player_invulnerable(t_health *health)
{
	if (!health)
		return (0);
	return (health->invulnerable_time > 0);
}

/*
** Screen shake effect when player takes damage
** Returns amount to shake (0-10 pixels)
*/
int	get_damage_screen_shake(t_health *health)
{
	if (!health)
		return (0);
	if (health->invulnerable_time > 25)
		return (3);
	else if (health->invulnerable_time > 15)
		return (2);
	else if (health->invulnerable_time > 0)
		return (1);
	return (0);
}

/*
** Get color tint for damage feedback
** Returns red tint intensity (0-255)
*/
int	get_damage_color_tint(t_health *health)
{
	if (!health || health->invulnerable_time == 0)
		return (0);
	return ((health->invulnerable_time * 255) / 30);
}
